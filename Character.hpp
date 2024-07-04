<<<<<<< HEAD
#include <iostream>
#include <string>

// 抽象类 Character
class Character {
public:
    Character(const std::string& name, int health, int attack)
        : name(name), health(health), attack(attack) {}

    virtual ~Character() {}

    // 纯虚函数
    virtual void attack(Character& target) = 0;
    virtual void takeDamage(int damage) = 0;

    // 访问者方法
    const std::string& getName() const { return name; }
    int getHealth() const { return health; }
    const int getPositionX() const { return x; }
    const int getPositionY() const { return y; }
protected:
    std::string name;
    int health;
    int attack;
    int x, y;
};

// 英雄类 Hero
class Hero : public Character {
public:
    Hero(const std::string& name, int health, int attack, const std::string& skill)
        : Character(name, health, attack), skill(skill) {}

    void attack(Character& target) override {
        target.takeDamage(attack);
    }

    void takeDamage(int damage) override {
        health -= damage;
    }

private:
    std::string skill;
};

// 怪兽类 Monster
class Monster : public Character {
public:
    Monster(const std::string& name, int health, int attack)
        : Character(name, health, attack) {}

    void attack(Character& target) override {
        target.takeDamage(attack);
    }

    void takeDamage(int damage) override {
        health -= damage;
    }
};

=======
#include <iostream>
#include <string>

// 抽象类 Character
class Character {
public:
    Character(const std::string& name, int health, int attack)
        : name(name), health(health), attack(attack) {}

    virtual ~Character() {}

    // 纯虚函数
    virtual void attack(Character& target) = 0;
    virtual void takeDamage(int damage) = 0;

    // 访问者方法
    const std::string& getName() const { return name; }
    int getHealth() const { return health; }
    const int getPositionX() const { return x; }
    const int getPositionY() const { return y; }
protected:
    std::string name;
    int health;
    int attack;
    int x, y;
};

// 英雄类 Hero
class Hero : public Character {
public:
    Hero(const std::string& name, int health, int attack, const std::string& skill)
        : Character(name, health, attack), skill(skill) {}

    void attack(Character& target) override {
        target.takeDamage(attack);
    }

    void takeDamage(int damage) override {
        health -= damage;
    }

private:
    std::string skill;
};

// 怪兽类 Monster
class Monster : public Character {
public:
    Monster(const std::string& name, int health, int attack)
        : Character(name, health, attack) {}

    void attack(Character& target) override {
        target.takeDamage(attack);
    }

    void takeDamage(int damage) override {
        health -= damage;
    }
};

>>>>>>> 187561aa7d0e60eab51382b759e2506ca786404b
