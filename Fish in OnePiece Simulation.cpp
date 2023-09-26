#include <iostream>
#include <string>
#include <vector>

class AbstractMonitor {
public:
    virtual void shot(double fish_weight, double catch_strength) = 0;
};

class PerformanceMonitor : public virtual AbstractMonitor {
protected:
    double fish_weight;
    double catch_strength;
    int net_throw;

public:
    PerformanceMonitor(double fish_weight, double catch_strength)
        : fish_weight(fish_weight), catch_strength(catch_strength), net_throw(0) {}

    void shot(double fish_weight, double catch_strength) override {
        while (net_throw < catch_strength) {
            net_throw += catch_strength;
        }
        std::cout << "Catch Strength: " << catch_strength << ", Fish Weight: " << fish_weight << std::endl;
    }

    double getFishWeight() const {
        return fish_weight;
    }
};

template <typename T>
class Volunteer {
private:
    int numVolunteers;
    std::string message;

public:
    Volunteer() : numVolunteers(0), message(" ") {}

    void addVolunteers(int num) {
        numVolunteers += num;
    }

    int getNumVolunteers() const {
        return numVolunteers;
    }

    void setMessage(const std::string& msg) {
        message = msg;
    }

    std::string getMessage() const {
        return message;
    }

    void messageToCustomer(T& customer) {
        customer.receiveMessage(message);
    }
};

class Customer {
public:
    void receiveMessage(const std::string& msg) {
        std::cout << "Received message from Volunteer: " << msg << std::endl;
    }
};

class Grub {
private:
    int proteinGrams;

public:
    Grub(int proteinGrams) : proteinGrams(proteinGrams) {}

    int getProteinGrams() const {
        return proteinGrams;
    }

    int getTimeReduction() const {
        if (proteinGrams == 5)
            return 1;
        else if (proteinGrams == 10)
            return 2;
        else if (proteinGrams == 15)
            return 3;
        return 0;
    }
};

class Feed {
private:
    int feedingTime;
    double feedingArea;
    int volunteerNum;
    int totalVolunteerTimeReduction;
    std::vector<Grub> grubs;
    std::vector<Volunteer<Customer>> volunteers;

public:
    Feed(int _feedingTime, double _feedingArea, int _volunteerNum)
        : feedingTime(_feedingTime), feedingArea(_feedingArea), volunteerNum(_volunteerNum), totalVolunteerTimeReduction(0) {}

    void addGrub(const Grub& grub) {
        grubs.push_back(grub);
    }

    void addVolunteer(const Volunteer<Customer>& volunteer) {
        volunteers.push_back(volunteer);
        totalVolunteerTimeReduction += volunteer.getNumVolunteers() * 5;
    }

    int getFeedingTime() const {
        int totalGrubTimeReduction = 0;
        for (const Grub& grub : grubs) {
            totalGrubTimeReduction += grub.getTimeReduction();
        }
        int finalFeedingTime = feedingTime - totalVolunteerTimeReduction;
        return finalFeedingTime;
    }

    double getFeedingArea() const {
        return feedingArea;
    }

    friend std::ostream& operator<<(std::ostream& os, const Feed& feed) {
        os << "Total Feeding Time: " << feed.getFeedingTime() << " minutes" << std::endl;
        return os;
    }
};

class FishForm {
public:
    FishForm(const std::string& name, double weight) : fishName(name), fishWeight(weight) {}
    virtual double priceDeterminant() = 0;
    void showDetails() {
        std::cout << "Fish Name: " << fishName << ", Price: " << priceDeterminant() << std::endl;
    }

protected:
    std::string fishName;
    double fishWeight;
};

class Tuna : public FishForm {
public:
    Tuna(const std::string& name, double weight) : FishForm(name, weight) {}
    double priceDeterminant() override {
        return fishWeight / 4.0;
    }
};

class Coral : public FishForm {
public:
    Coral(const std::string& name, double weight) : FishForm(name, weight) {}
    double priceDeterminant() override {
        return fishWeight / 3.0;
    }
};

class Hilsha : public FishForm {
public:
    Hilsha(const std::string& name, double weight) : FishForm(name, weight) {}
    double priceDeterminant() override {
        return fishWeight / 2.0;
    }
};

int main() {
    int feedingTime = 60;
    double feedingArea = 15.0;
    int volunteerNum = 5;
    Feed feed(feedingTime, feedingArea, volunteerNum);

    Grub grub1(5);
    Grub grub2(10);
    Grub grub3(15);

    Volunteer<Customer> volunteer1;
    Volunteer<Customer> volunteer2;
    volunteer2.addVolunteers(1); // Assuming 1 volunteer

    feed.addGrub(grub1);
    feed.addGrub(grub2);
    feed.addGrub(grub3);
    feed.addVolunteer(volunteer1);
    feed.addVolunteer(volunteer2);

    std::cout << feed; // Use operator overloading to print the feed details

    PerformanceMonitor monitor(10.0, 5.0);
    monitor.shot(10.0, 5.0);

    // Test the FishForm and its subclasses
    Tuna tuna("Bluefin Tuna", monitor.getFishWeight());
    Coral coral("Red Coral Fish", monitor.getFishWeight());
    Hilsha hilsha("Ilish Hilsha", monitor.getFishWeight());

    tuna.showDetails();
    coral.showDetails();
    hilsha.showDetails();

    return 0;
}
