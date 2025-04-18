#include <iostream>
#include <memory>

// 抽象产品A
class AbstractProductA {
public:
    virtual void use() const = 0;
    virtual ~AbstractProductA() = default;
};

// 抽象产品B
class AbstractProductB {
public:
    virtual void use() const = 0;
    virtual ~AbstractProductB() = default;
};

// 具体产品A1
class ConcreteProductA1 : public AbstractProductA {
public:
    void use() const override {
        std::cout << "Using Product A1" << std::endl;
    }
};

// 具体产品A2
class ConcreteProductA2 : public AbstractProductA {
public:
    void use() const override {
        std::cout << "Using Product A2" << std::endl;
    }
};

// 具体产品B1
class ConcreteProductB1 : public AbstractProductB {
public:
    void use() const override {
        std::cout << "Using Product B1" << std::endl;
    }
};

// 具体产品B2
class ConcreteProductB2 : public AbstractProductB {
public:
    void use() const override {
        std::cout << "Using Product B2" << std::endl;
    }
};

// 抽象工厂
class AbstractFactory {
public:
    virtual std::unique_ptr<AbstractProductA> createProductA() const = 0;
    virtual std::unique_ptr<AbstractProductB> createProductB() const = 0;
    virtual ~AbstractFactory() = default;
};

// 具体工厂1
class ConcreteFactory1 : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createProductA() const override {
        return std::make_unique<ConcreteProductA1>();
    }

    std::unique_ptr<AbstractProductB> createProductB() const override {
        return std::make_unique<ConcreteProductB1>();
    }
};

// 具体工厂2
class ConcreteFactory2 : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createProductA() const override {
        return std::make_unique<ConcreteProductA2>();
    }

    std::unique_ptr<AbstractProductB> createProductB() const override {
        return std::make_unique<ConcreteProductB2>();
    }
};

// 客户端代码
void clientCode(const AbstractFactory& factory) {
    auto productA = factory.createProductA();
    auto productB = factory.createProductB();
    productA->use();
    productB->use();
}

// 抽象船体类
class Hull {
public:
    virtual void describe() const = 0;
    virtual ~Hull() = default;
};

// 抽象引擎类
class Engine {
public:
    virtual void describe() const = 0;
    virtual ~Engine() = default;
};

// 抽象武器类
class Weapon {
public:
    virtual void describe() const = 0;
    virtual ~Weapon() = default;
};

// 具体船体类
class StandardHull : public Hull {
public:
    void describe() const override {
        std::cout << "Standard Hull" << std::endl;
    }
};

class GoldHull : public Hull {
public:
    void describe() const override {
        std::cout << "Gold Hull" << std::endl;
    }
};

class PlatinumHull : public Hull {
public:
    void describe() const override {
        std::cout << "Platinum Hull" << std::endl;
    }
};

// 具体引擎类
class StandardEngine : public Engine {
public:
    void describe() const override {
        std::cout << "Standard Engine" << std::endl;
    }
};

class GoldEngine : public Engine {
public:
    void describe() const override {
        std::cout << "Gold Engine" << std::endl;
    }
};

class PlatinumEngine : public Engine {
public:
    void describe() const override {
        std::cout << "Platinum Engine" << std::endl;
    }
};

// 具体武器类
class StandardWeapon : public Weapon {
public:
    void describe() const override {
        std::cout << "Standard Weapon" << std::endl;
    }
};

class GoldWeapon : public Weapon {
public:
    void describe() const override {
        std::cout << "Gold Weapon" << std::endl;
    }
};

class PlatinumWeapon : public Weapon {
public:
    void describe() const override {
        std::cout << "Platinum Weapon" << std::endl;
    }
};

// 抽象工厂类
class ShipFactory {
public:
    virtual std::unique_ptr<Hull> createHull() const = 0;
    virtual std::unique_ptr<Engine> createEngine() const = 0;
    virtual std::unique_ptr<Weapon> createWeapon() const = 0;
    virtual ~ShipFactory() = default;
};

// 具体工厂类
class StandardShipFactory : public ShipFactory {
public:
    std::unique_ptr<Hull> createHull() const override {
        return std::make_unique<StandardHull>();
    }

    std::unique_ptr<Engine> createEngine() const override {
        return std::make_unique<StandardEngine>();
    }

    std::unique_ptr<Weapon> createWeapon() const override {
        return std::make_unique<StandardWeapon>();
    }
};

class GoldShipFactory : public ShipFactory {
public:
    std::unique_ptr<Hull> createHull() const override {
        return std::make_unique<GoldHull>();
    }

    std::unique_ptr<Engine> createEngine() const override {
        return std::make_unique<GoldEngine>();
    }

    std::unique_ptr<Weapon> createWeapon() const override {
        return std::make_unique<GoldWeapon>();
    }
};

class PlatinumShipFactory : public ShipFactory {
public:
    std::unique_ptr<Hull> createHull() const override {
        return std::make_unique<PlatinumHull>();
    }

    std::unique_ptr<Engine> createEngine() const override {
        return std::make_unique<PlatinumEngine>();
    }

    std::unique_ptr<Weapon> createWeapon() const override {
        return std::make_unique<PlatinumWeapon>();
    }
};

// 船类
class Ship {
private:
    std::unique_ptr<Hull> hull;
    std::unique_ptr<Engine> engine;
    std::unique_ptr<Weapon> weapon;

public:
    Ship(std::unique_ptr<Hull> h, std::unique_ptr<Engine> e, std::unique_ptr<Weapon> w)
        : hull(std::move(h)), engine(std::move(e)), weapon(std::move(w)) {}

    void describe() const {
        std::cout << "Ship description:" << std::endl;
        hull->describe();
        engine->describe();
        weapon->describe();
    }
};

// 客户端代码更新
void clientCode(const ShipFactory& factory) {
    auto hull = factory.createHull();
    auto engine = factory.createEngine();
    auto weapon = factory.createWeapon();

    Ship ship(std::move(hull), std::move(engine), std::move(weapon));
    ship.describe();
}

int main() {
    std::cout << "App: Using ConcreteFactory1." << std::endl;
    ConcreteFactory1 factory1;
    clientCode(factory1);

    std::cout << "App: Using ConcreteFactory2." << std::endl;
    ConcreteFactory2 factory2;
    clientCode(factory2);

    std::cout << "Producing Standard Ship:" << std::endl;
    StandardShipFactory standardFactory;
    clientCode(standardFactory);

    std::cout << "\nProducing Gold Ship:" << std::endl;
    GoldShipFactory goldFactory;
    clientCode(goldFactory);

    std::cout << "\nProducing Platinum Ship:" << std::endl;
    PlatinumShipFactory platinumFactory;
    clientCode(platinumFactory);

    return 0;
}