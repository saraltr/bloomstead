#ifndef PLANT_H
#define PLANT_H

#include <string>

// growth stages a plant can go through
enum class GrowthStage
{
    Seedling,
    Budding,
    Blooming,
    Mature,
    Dead
};

class Plant
{
protected:
    // name of the plant
    std::string name;
    int waterLevel;
    GrowthStage stage;
    bool hasPests;
    bool hasWeeds;

    int pestDamageCount; // how many times pests have damaged the plant
    int weedDamageCount; // how many times weeds affected it

    // returns true if the plant is alive
    bool alive;

    static const int damageThreshold = 3; // damage count before plant dies

    void checkDeath(); // checks if plant should die due to damage

private:
    bool planted; // plant status

public:
    Plant(const std::string &name);
    virtual ~Plant() {}

    // logic to move to the next growth stage
    virtual void grow();
    // returns a string describing the plant
    virtual std::string getType() const;
    // returns water needed to reach next stage
    virtual int nextStage() const;

    // increases water level
    void water();
    // regresses growth stage (if not treated)
    void reduceGrowth();

    int getWaterLevel() const;
    GrowthStage getGrowthStage() const;
    std::string getName() const { return name; }
    // string for current stage
    std::string getStageName() const;

    // pests
    void applyPestDamage(); // flags plant as having pests
    void increasePestDamage();  // increases pest damage count
    void clearPests();  // removes pests
    bool checkPests() const;    // checks if pests are present

    // weeds
    void applyWeedGrowth(); // flags plant as having weeds
    void increaseWeedDamage();  // increases weed damage count
    void clearWeeds();  // removes weeds
    bool checkWeeds() const;    // checks if weeds are present

    bool isAlive() const;   // whether the plant is alive
    void reset();   // resets plant to initial state

    void plant();   // marks the plant as planted
    bool isPlanted() const; // checks if it's planted
};

#endif
