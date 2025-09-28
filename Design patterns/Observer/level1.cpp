#include <bits/stdc++.h>
using namespace std;

// Abstract Observer interface
class ISubscriber {
public:
    virtual void update() = 0;
    virtual ~ISubscriber() {}  // virtual destructor for interface
};
    
// Abstract Observable interface
class IChannel {
public:
    virtual void subscribe(ISubscriber* subscriber) = 0;
    virtual void unsubscribe(ISubscriber* subscriber) = 0;
    virtual void notifySubscribers() = 0;
    virtual ~IChannel() {}
};

// Concrete Observable: a YouTube channel
class Channel : public IChannel {
private:
    vector<ISubscriber*> subscribers;  // list of subscribers
    string name;
    string latestVideo;               // latest uploaded video title
public:
    Channel(const string& name) {
        this->name = name;
    }

    // Add a subscriber (avoid duplicates)
    void subscribe(ISubscriber* subscriber) override {
        if (find(subscribers.begin(), subscribers.end(), subscriber) == subscribers.end()) {
            subscribers.push_back(subscriber);
        }
    }

    // Remove a subscriber if present
    void unsubscribe(ISubscriber* subscriber) override {
        auto it = find(subscribers.begin(), subscribers.end(), subscriber);
        if (it != subscribers.end()) {
            subscribers.erase(it);
        }
    }

    // Notify all subscribers of the latest video
    void notifySubscribers() override {
        for (ISubscriber* sub : subscribers) {
            sub->update();
        }
    }

    // Upload a new video and notify all subscribers
    void uploadVideo(const string& title) {
        latestVideo = title;
        cout << "\n[" << name << " uploaded \"" << title << "\"]\n";
        notifySubscribers();
    }

    // Read video data
    string getVideoData() {
        return "\nCheckout our new Video : " + latestVideo + "\n";
    }
};

// Concrete Observer: a YouTube channel subscriber
class Subscriber : public ISubscriber {
private:
    string name;
    Channel* channel;
public:
    Subscriber(const string& name, Channel* channel) {
        this->name = name;
        this->channel = channel;
    }

    // Called by Channel; prints notification message
    void update() override {
        cout << "Hey " << name << "," << this->channel->getVideoData();
    }
};

int main() {
    // Create a channel and subscribers
    Channel* channel = new Channel("T-Series");

    Subscriber* subs1 = new Subscriber("Anish", channel);
    Subscriber* subs2 = new Subscriber("Suyash", channel);

    // Anish and Suyash subscribe to T-Series
    channel->subscribe(subs1);
    channel->subscribe(subs2);

    // Upload a video: both Anish and Suyash are notified
    channel->uploadVideo("Observer Pattern Tutorial");

    // Anish unsubscribes; Suyash remains subscribed
    channel->unsubscribe(subs1);

    // Upload another video: only Suyash is notified
    channel->uploadVideo("Decorator Pattern Tutorial");

    return 0;
}