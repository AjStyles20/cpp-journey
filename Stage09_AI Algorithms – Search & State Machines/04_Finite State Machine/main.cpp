#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <map>
#include <ctime>
#include <unistd.h>

using namespace std;

// Event types
enum class Event {
    EnemySpotted,
    EnemyLost,
    LowBattery,
    BatteryFull,
    InvestigationComplete,
    NothingHappened
};

// Abstract State class
class State {
public:
    virtual void enter() = 0;
    virtual void exit() {}
    virtual void update() = 0;
    virtual void handleEvent(Event event) = 0;
    virtual string getName() const = 0;
    virtual ~State() {}
};

// Forward declare RobotFSM
class RobotFSM;

// Concrete State declarations
class PatrolState : public State {
    RobotFSM* context;
public:
    PatrolState(RobotFSM* context);
    void enter() override;
    void update() override;
    void handleEvent(Event event) override;
    string getName() const override;
};

class ChaseState : public State {
    RobotFSM* context;
public:
    ChaseState(RobotFSM* context);
    void enter() override;
    void update() override;
    void handleEvent(Event event) override;
    string getName() const override;
};

class RechargeState : public State {
    RobotFSM* context;
public:
    RechargeState(RobotFSM* context);
    void enter() override;
    void update() override;
    void handleEvent(Event event) override;
    string getName() const override;
};

class InvestigateState : public State {
    RobotFSM* context;
public:
    InvestigateState(RobotFSM* context);
    void enter() override;
    void update() override;
    void handleEvent(Event event) override;
    string getName() const override;
};

// Context class (Finite State Machine)
class RobotFSM {
private:
    shared_ptr<State> currentState;
    double batteryLevel = 100.0;
    double enemyDistance = 100.0;
    bool enemyVisible = false;
    int investigationCount = 0;
    
public:
    RobotFSM(shared_ptr<State> initialState);
    
    void setState(shared_ptr<State> newState);
    shared_ptr<State> getCurrentState() const;
    
    void update();
    void triggerEvent(Event event);
    
    double getBatteryLevel() const { return batteryLevel; }
    void setBatteryLevel(double level) { batteryLevel = level; }
    
    double getEnemyDistance() const { return enemyDistance; }
    void setEnemyDistance(double distance) { enemyDistance = distance; }
    
    bool isEnemyVisible() const { return enemyVisible; }
    void setEnemyVisible(bool visible) { enemyVisible = visible; }
    
    int getInvestigationCount() const { return investigationCount; }
    void resetInvestigation() { investigationCount = 0; }
    void incrementInvestigation() { investigationCount++; }
};

// Now implement the state classes after RobotFSM is fully defined

PatrolState::PatrolState(RobotFSM* context) : context(context) {}

void PatrolState::enter() {
    cout << "Entering Patrol state. Scanning the area...\n";
}

void PatrolState::update() {
    cout << "Patrolling... Battery: " << context->getBatteryLevel() << "%\n";
    context->setBatteryLevel(context->getBatteryLevel() - 0.5);
}

void PatrolState::handleEvent(Event event) {
    switch(event) {
        case Event::EnemySpotted:
            cout << "Enemy spotted while patrolling!\n";
            context->setState(make_shared<ChaseState>(context));
            break;
        case Event::LowBattery:
            cout << "Battery low during patrol!\n";
            context->setState(make_shared<RechargeState>(context));
            break;
        case Event::NothingHappened:
            break;
        default:
            cout << "PatrolState: Unhandled event\n";
    }
}

string PatrolState::getName() const { return "Patrol"; }

ChaseState::ChaseState(RobotFSM* context) : context(context) {}

void ChaseState::enter() {
    cout << "Entering Chase state. Engaging target!\n";
}

void ChaseState::update() {
    double distance = context->getEnemyDistance();
    
    if (distance > 0) {
        cout << "Chasing enemy! Distance: " << distance << "m. Battery: " 
             << context->getBatteryLevel() << "%\n";
        context->setEnemyDistance(distance - 5);
        context->setBatteryLevel(context->getBatteryLevel() - 1.5);
    }
    
    if (distance <= 0) {
        cout << "Enemy captured!\n";
        context->triggerEvent(Event::EnemyLost);
    }
}

void ChaseState::handleEvent(Event event) {
    switch(event) {
        case Event::EnemyLost:
            cout << "Enemy lost during chase!\n";
            context->setState(make_shared<InvestigateState>(context));
            break;
        case Event::LowBattery:
            cout << "Battery critical during chase!\n";
            context->setState(make_shared<RechargeState>(context));
            break;
        case Event::NothingHappened:
            break;
        default:
            cout << "ChaseState: Unhandled event\n";
    }
}

string ChaseState::getName() const { return "Chase"; }

RechargeState::RechargeState(RobotFSM* context) : context(context) {}

void RechargeState::enter() {
    cout << "Entering Recharge state. Connecting to power...\n";
}

void RechargeState::update() {
    double battery = context->getBatteryLevel();
    cout << "Recharging... Battery: " << battery << "%\n";
    
    if (battery < 100) {
        context->setBatteryLevel(min(100.0, battery + 10));
    } else {
        context->triggerEvent(Event::BatteryFull);
    }
}

void RechargeState::handleEvent(Event event) {
    switch(event) {
        case Event::BatteryFull:
            cout << "Battery fully charged!\n";
            context->setState(make_shared<PatrolState>(context));
            break;
        case Event::EnemySpotted:
            cout << "Enemy spotted while recharging! Ignoring...\n";
            break;
        case Event::NothingHappened:
            break;
        default:
            cout << "RechargeState: Unhandled event\n";
    }
}

string RechargeState::getName() const { return "Recharge"; }

InvestigateState::InvestigateState(RobotFSM* context) : context(context) {}

void InvestigateState::enter() {
    cout << "Entering Investigate state. Searching last known position...\n";
    context->resetInvestigation();
}

void InvestigateState::update() {
    int count = context->getInvestigationCount();
    cout << "Investigating... Search attempts: " << count << "/3\n";
    context->incrementInvestigation();
    context->setBatteryLevel(context->getBatteryLevel() - 0.8);
    
    if (count >= 3) {
        context->triggerEvent(Event::InvestigationComplete);
    }
}

void InvestigateState::handleEvent(Event event) {
    switch(event) {
        case Event::InvestigationComplete:
            cout << "Investigation complete. No enemy found.\n";
            context->setState(make_shared<PatrolState>(context));
            break;
        case Event::EnemySpotted:
            cout << "Enemy found during investigation!\n";
            context->setState(make_shared<ChaseState>(context));
            break;
        case Event::LowBattery:
            cout << "Battery low during investigation!\n";
            context->setState(make_shared<RechargeState>(context));
            break;
        case Event::NothingHappened:
            break;
        default:
            cout << "InvestigateState: Unhandled event\n";
    }
}

string InvestigateState::getName() const { return "Investigate"; }

// RobotFSM implementation
RobotFSM::RobotFSM(shared_ptr<State> initialState) 
    : currentState(initialState) {
    currentState->enter();
}

void RobotFSM::setState(shared_ptr<State> newState) {
    cout << "Transitioning from " << currentState->getName() 
         << " to " << newState->getName() << " state\n";
    currentState->exit();
    currentState = newState;
    currentState->enter();
}

void RobotFSM::update() {
    currentState->update();
    
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<int> visibilityDist(1, 20);
    
    if (visibilityDist(gen) == 1) {
        enemyVisible = true;
        triggerEvent(Event::EnemySpotted);
    } else if (enemyVisible && visibilityDist(gen) == 1) {
        enemyVisible = false;
        triggerEvent(Event::EnemyLost);
    }
    
    if (batteryLevel < 20 && currentState->getName() != "Recharge") {
        triggerEvent(Event::LowBattery);
    }
}

void RobotFSM::triggerEvent(Event event) {
    currentState->handleEvent(event);
}

Event generateRandomEvent() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<int> dist(0, 100);
    
    int r = dist(gen);
    if (r < 10) return Event::EnemySpotted;
    if (r < 20) return Event::EnemyLost;
    if (r < 25) return Event::LowBattery;
    if (r < 30) return Event::BatteryFull;
    if (r < 35) return Event::InvestigationComplete;
    return Event::NothingHappened;
}

int main() {
    RobotFSM fsm(make_shared<PatrolState>(&fsm));
    
    cout << "\n===== ROBOT FSM SIMULATION =====\n";
    cout << "Starting in Patrol state\n\n";
    
    for (int i = 0; i < 50; i++) {
        cout << "\n--- Update " << i << " ---\n";
        fsm.update();
        
        Event event = generateRandomEvent();
        if (event != Event::NothingHappened) {
            cout << "EVENT: ";
            switch(event) {
                case Event::EnemySpotted: cout << "Enemy Spotted"; break;
                case Event::EnemyLost: cout << "Enemy Lost"; break;
                case Event::LowBattery: cout << "Low Battery"; break;
                case Event::BatteryFull: cout << "Battery Full"; break;
                case Event::InvestigationComplete: cout << "Investigation Complete"; break;
                default: cout << "Unknown Event"; break;
            }
            cout << endl;
            fsm.triggerEvent(event);
        }
        usleep(500000);
    }
    
    cout << "\n===== SIMULATION COMPLETE =====\n";
    return 0;
}