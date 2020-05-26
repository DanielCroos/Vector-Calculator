#include <iostream>
#include <stdexcept>
#include <cmath>

class Vector{
public:
    Vector(std::size_t dimension, double def=0);
    ~Vector();
    std::size_t get_dim()const;
    double get_value(std::size_t dimension)const;
    void set_value(std::size_t dimension, double value);
    Vector operator+ (Vector const &b); //Vector addition
    double operator*(Vector const &b);  //dot product
    Vector operator*(double scalar);    //scalar multiplication
    Vector operator/(Vector const &b);  //cross product
    bool operator=(Vector const &b);
    void print()const;
    void print_polar()const;
private:
    std::size_t dim;
    double* p_array;
};

Vector::Vector(std::size_t dimension, double def){
    if (dimension>0){
        dim = dimension;
        p_array = new double [dim]{};
        
        for (std::size_t i{0}; i<dim; i++){
            p_array[i] = def;
        }
    }
    else{
        throw std::invalid_argument("A vector must have dimension greater than 0");
    }
}

Vector::~Vector(){
    delete [] p_array;
    p_array = nullptr;
}

std::size_t Vector::get_dim()const{
    return dim;
}

double Vector::get_value(std::size_t dimension)const{
    if ((dimension>get_dim())||dimension<=0){
        throw std::invalid_argument("The vector does not exist in the same number of dimensions as the argument");
    }
    else{
        return p_array[dimension-1];
    }
}

void Vector::set_value(std::size_t dimension, double value){
    if (dimension>get_dim()){
        Vector b(dimension);
        
        for (std::size_t i{0}; i<get_dim(); i++){
            b.p_array[i] = p_array[i];
        }
        for (std::size_t i{get_dim()}; i<(dimension-1); i++){
            b.p_array[i] = 0;
        }
        b.p_array[dimension-1] = value;
        delete [] p_array;
        p_array = b.p_array;
        b.p_array = nullptr;
    }
    else{
        p_array[dimension-1] = value;
    }
}

Vector Vector::operator +(Vector const &b){
    if (get_dim()==b.get_dim()){
        Vector c(get_dim(),0);
        
        for (std::size_t i{1}; i<=(b.get_dim()); i++){
            c.set_value(i, get_value(i)+b.get_value(i));
        }
        return c;
    }
    else{
        throw std::domain_error ("Vectors must be of same dimension to perform addition");
    }
}

double Vector::operator*(Vector const &b){
    if (get_dim()==b.get_dim()){
        double output{0};
            for (std::size_t i{1}; i<=(b.get_dim()); i++){
                output += get_value(i)*b.get_value(i);
            }
            return output;
        }
    else{
        throw std::domain_error ("Vectors must be of same dimension to perform dot product");
    }
}

Vector Vector::operator/(Vector const &b){
    if ((get_dim()==3)&&(b.get_dim())==3){
        Vector c(3);
        c.set_value(1, get_value(2)*b.get_value(3)-get_value(3)*b.get_value(2));
        c.set_value(2, get_value(3)*b.get_value(1)-get_value(1)*b.get_value(3));
        c.set_value(3, get_value(1)*b.get_value(2)-get_value(2)*b.get_value(1));
        return c;
    }
    else{
        throw std::domain_error ("Vectors must be of 3 dimension to perform cross product");
    }
}

Vector Vector::operator*(double scalar){
    Vector c(get_dim());
    for (std::size_t i{1};i<=get_dim();i++){
        c.set_value(i, get_value(i)*scalar);
    }
    return c;
}

bool Vector::operator=(Vector const &b){
    if (get_dim()==b.get_dim()){
        std::size_t i{1};
        while ((get_value(i)==b.get_value(i))&&(i<get_dim())){
            i++;
        }
        if (get_value(i)==b.get_value(i)) i++;
        return (i-1 == get_dim());
    }
    else return false;
}

void Vector::print()const{
    for (std::size_t i{0};i<get_dim();i++){
        std::cout<<"X_"<<i+1<<": "<<get_value(i+1)<<std::endl;
    }
}

void Vector::print_polar()const{
    double r_val{0};
    for(std::size_t i{1};i<=get_dim();i++){
        r_val+=get_value(i)*get_value(i);
    }
    r_val = sqrt(r_val);
    std::cout<<"Distance from origin = "<<r_val<<std::endl;
    
    if (r_val != 0){
        for(std::size_t i{1};i<get_dim();i++){
            std::cout<<"Angle from X"<<i<<" = "<<acos(get_value(i)/r_val)/(2*3.14149)*360<<std::endl;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main();

int main(){
    bool check {true};
    unsigned char input{};
    std::cout<<"Welcome to the vector calculator"<<std::endl<<"What operation would you like to perform today?"<<std::endl;
    
    while (check){
        std::cout<<"Type 1 for addition"<<std::endl<<"Type 2 for subtraction"<<std::endl;
        std::cout<<"Type 3 for dot product"<<std::endl<<"Type 4 for cross product"<<std::endl<<"Type 5 for scalar multiplication"<<std::endl;
        std::cout<<"Type 6 to check if they are equal"<<std::endl<<"Type 7 to calculate Norm"<<std::endl;
        std::cout<<"Type 8 to convert to polar coordinates"<<std::endl<<"Type 9 to quit"<<std::endl;
        
        while(check){
            std::cin>>input;
            
            if ((input>'0')&&(input<='9')){
                check = false;
            }
            else{
                std::cout<<"That is not an accepted input please try again"<<std::endl;
            }
        }
        if (input == '9') break;
        
        std::size_t dim_1{};
        std::cout<<"Enter the number of dimensions for your vector"<<std::endl;
        std::cin>>dim_1;

        Vector a(dim_1);
        
        for (std::size_t i{1};i<=dim_1;i++){
            std::cout<<"Input value for X"<<i<<std::endl;
            double value{};
            std::cin>>value;
            a.set_value(i, value);
        }
        
        if ((input!='5')&&(input!='7')&&(input!='8')){
            std::size_t dim_2{};
            std::cout<<"Enter the number dimensions of your second vector"<<std::endl;
            std::cin>>dim_2;
            Vector b(dim_2);
            
            if (input=='1'){
                for (std::size_t i{1};i<=dim_2;i++){
                    std::cout<<"Input value for X"<<i<<std::endl;
                    double value{};
                    std::cin>>value;
                    b.set_value(i, value);
                }
                (a+b).print();
            }
            else if(input=='2'){
                for (std::size_t i{1};i<=dim_2;i++){
                    std::cout<<"Input value for X"<<i<<std::endl;
                    double value{};
                    std::cin>>value;
                    b.set_value(i, -1*value);
                }
                (a+b).print();
            }
            else if (input=='3'){
                for (std::size_t i{1};i<=dim_2;i++){
                    std::cout<<"Input value for X"<<i<<std::endl;
                    double value{};
                    std::cin>>value;
                    b.set_value(i, value);
                }
                std::cout<<a*b<<std::endl;
            }
            else if (input=='4'){
                for (std::size_t i{1};i<=dim_2;i++){
                    std::cout<<"Input value for X"<<i<<std::endl;
                    double value{};
                    std::cin>>value;
                    b.set_value(i,value);
                }
                (a/b).print();
            }
            else {
                for (std::size_t i{1};i<=dim_2;i++){
                std::cout<<"Input value for X"<<i<<std::endl;
                double value{};
                std::cin>>value;
                b.set_value(i,value);
                }
                std::cout<<(a = b)<<std::endl;
            }
            a.~Vector();
            b.~Vector();
        }
        else if(input =='5'){
            std::cout<<"Enter the scalar amount"<<std::endl;
            double scalar;
            std::cin>>scalar;
            (a*scalar).print();
            a.~Vector();
        }
        else if (input=='8'){
            a.print_polar();
            a.~Vector();
        }
        else {
            double norm{sqrt(a*a)};
            std::cout<<"The norm = "<<norm<<std::endl;
            a.~Vector();
        }
        std::cout<<std::endl;
        
        input='0';
        check = true;
        while ((check)){
            std::cout<<"Would you like to perform another calculation"<<std::endl;
            std::cout<<"Enter 1 for Yes"<<std::endl<<"Enter 2 for No"<<std::endl;
            
            std::cin>>input;
            
            if (input == '1') break;
            else if (input == '2') check = 0;
            else{
                std::cout<<"That is not an accepted input please try again"<<std::endl<<std::endl;
            }
        }
    }
    std::cout<<"Thank you for using this Vector calculator"<<std::endl<<"Goodbye"<<std::endl;
    return 0;
}
