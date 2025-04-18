#include <iostream>
#include <memory>
#include <string>

// House类及其子类
class House {
public:
    std::string foundation;
    std::string structure;
    std::string roof;
    std::string interior;
    std::string exterior;

public:
    virtual void showDetails() const = 0;
    virtual ~House() = default;
};

class WoodenHouse : public House {
public:
    void showDetails() const override {
        std::cout << "Wooden House with:\n"
                  << "Foundation: " << foundation << "\n"
                  << "Structure: " << structure << "\n"
                  << "Roof: " << roof << "\n"
                  << "Interior: " << interior << "\n"
                  << "Exterior: " << exterior << "\n";
    }
};

class BrickHouse : public House {
public:
    void showDetails() const override {
        std::cout << "Brick House with:\n"
                  << "Foundation: " << foundation << "\n"
                  << "Structure: " << structure << "\n"
                  << "Roof: " << roof << "\n"
                  << "Interior: " << interior << "\n"
                  << "Exterior: " << exterior << "\n";
    }
};

class GlassHouse : public House {
public:
    void showDetails() const override {
        std::cout << "Glass House with:\n"
                  << "Foundation: " << foundation << "\n"
                  << "Structure: " << structure << "\n"
                  << "Roof: " << roof << "\n"
                  << "Interior: " << interior << "\n"
                  << "Exterior: " << exterior << "\n";
    }
};

// HouseBuilder类及其子类
class HouseBuilder {
protected:
    std::unique_ptr<House> house;

public:
    virtual ~HouseBuilder() = default;

    virtual void createNewHouse() = 0; // 改为纯虚函数

    virtual void buildFoundation() = 0;
    virtual void buildStructure() = 0;
    virtual void buildRoof() = 0;
    virtual void buildInterior() = 0;
    virtual void buildExterior() = 0;

    std::unique_ptr<House> getHouse() {
        return std::move(house);
    }
};

class WoodenHouseBuilder : public HouseBuilder {
public:
    void createNewHouse() override {
        house = std::make_unique<WoodenHouse>();
    }

    void buildFoundation() override {
        house->foundation = "Wooden Foundation";
    }

    void buildStructure() override {
        house->structure = "Wooden Structure";
    }

    void buildRoof() override {
        house->roof = "Wooden Roof";
    }

    void buildInterior() override {
        house->interior = "Wooden Interior";
    }

    void buildExterior() override {
        house->exterior = "Wooden Exterior";
    }
};

class BrickHouseBuilder : public HouseBuilder {
public:
    void createNewHouse() override {
        house = std::make_unique<BrickHouse>();
    }

    void buildFoundation() override {
        house->foundation = "Brick Foundation";
    }

    void buildStructure() override {
        house->structure = "Brick Structure";
    }

    void buildRoof() override {
        house->roof = "Brick Roof";
    }

    void buildInterior() override {
        house->interior = "Brick Interior";
    }

    void buildExterior() override {
        house->exterior = "Brick Exterior";
    }
};

class GlassHouseBuilder : public HouseBuilder {
public:
    void createNewHouse() override {
        house = std::make_unique<GlassHouse>();
    }

    void buildFoundation() override {
        house->foundation = "Glass Foundation";
    }

    void buildStructure() override {
        house->structure = "Glass Structure";
    }

    void buildRoof() override {
        house->roof = "Glass Roof";
    }

    void buildInterior() override {
        house->interior = "Glass Interior";
    }

    void buildExterior() override {
        house->exterior = "Glass Exterior";
    }
};

// Director类
class Director {
private:
    HouseBuilder* builder;

public:
    void setBuilder(HouseBuilder* b) {
        builder = b;
    }

    std::unique_ptr<House> constructHouse() {
        builder->createNewHouse();
        builder->buildFoundation();
        builder->buildStructure();
        builder->buildRoof();
        builder->buildInterior();
        builder->buildExterior();
        return builder->getHouse();
    }
};

// 客户端代码
int main() {
    Director director;

    WoodenHouseBuilder woodenBuilder;
    director.setBuilder(&woodenBuilder);
    auto woodenHouse = director.constructHouse();
    woodenHouse->showDetails();

    BrickHouseBuilder brickBuilder;
    director.setBuilder(&brickBuilder);
    auto brickHouse = director.constructHouse();
    brickHouse->showDetails();

    GlassHouseBuilder glassBuilder;
    director.setBuilder(&glassBuilder);
    auto glassHouse = director.constructHouse();
    glassHouse->showDetails();

    return 0;
}