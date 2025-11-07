
#include <iostream>
#include <cmath> 

class Field {
protected:
    double *value;

public:
    // Default constructor
    Field() : value(new double[3]{0.0, 0.0, 0.0}) {}

    Field(double x, double y, double z) : value(new double[3]{x, y, z}) {}

    // Destructor
    ~Field() {
        delete[] value;
    }

    // magnitude of the field
    void printMagnitude() {
        double magnitude = std::sqrt(std::pow(value[0], 2) + std::pow(value[1], 2) + std::pow(value[2], 2));
        std::cout << "Field magnitude: " << magnitude << std::endl; 
    }

    // Function to print the components
    void printComponents() {
        std::cout << "Field components: <" << value[0] << ", " << value[1] << ", " << value[2] << ">" << std::endl;
    }
    	
    // Getter function to access components
    double* getComponents() {
        return value;
    } 
};

class ElectricField : public Field {
private:
	double E;
    	double epsilon = 8.85e-12;

public:
    // Default constructor
    ElectricField() : Field() {}

    // Constructor
    ElectricField(double x, double y, double z) : Field(x, y, z) {}

    // Destructor
    ~ElectricField() {}

    void calElectricField(double r, double Q) {
        
        double magnitude = Q / (4.0 * M_PI * std::pow(r, 2) * epsilon);
        double *E = getComponents();
        E[0] = magnitude;
        E[1] = magnitude;
        E[2] = magnitude;
    }

    // Overload + operator
    ElectricField operator+( ElectricField& var) {
        double* thisComponents = getComponents();
        double* varComponents = var.getComponents();
        return ElectricField(thisComponents[0] + varComponents[0], 
                             thisComponents[1] + varComponents[1], 
                             thisComponents[2] + varComponents[2]);
    }

    // Overload << operator
    friend std::ostream& operator<<(std::ostream& os, ElectricField& ef);
};
std::ostream& operator<<(std::ostream& os, ElectricField& ef) {
    double* E = ef.getComponents();
    os << "Electric Field Components: <" << E[0] << ", " 
       << E[1] << ", " << E[2] << ">";
    return os;
}

class MagneticField : public Field {
public:
    // Default constructor
    MagneticField() : Field() {}
    MagneticField(double x, double y, double z) : Field(x, y, z) {}
    ~MagneticField() {}
};


int main() {
    // Creating ElectricField objects
    ElectricField e1(1e6, 1e4, 9.0);
    ElectricField e2(0.5, 1.5, 2.5);

    std::cout << "e1 ";
    e1.printMagnitude();
    std::cout << "e2 ";
    e2.printMagnitude();

    // overload << operator
    std::cout << "e1: " << e1 << std::endl;
    std::cout << "e2: " << e2 << std::endl;

    // components for e1
    double Q = 2e-6; 
    double r = 0.1;
    std::cout << "\nCalculating electric field for Q=" << Q << " at r=" << r << std::endl;
    e1.calElectricField(r, Q);
    e1.printComponents();
    e1.printMagnitude();

    // overload + operator
    ElectricField e3 = e1 + e2;
    std::cout << "\ne3 (e1 + e2): ";
    e3.printComponents();
    e3.printMagnitude();
    std::cout << "e3: " << e3 << std::endl;

    // MagneticField object
    MagneticField m1(0.1, 0.2, 0.3);
    std::cout << "\nm1 Magnetic Field components: ";
    m1.printComponents();
    m1.printMagnitude();

    return 0;
}
