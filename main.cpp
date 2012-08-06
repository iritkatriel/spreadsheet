//
//  main.cpp
//  spreadsheet
//
//  Created by Irit Katriel on 15/07/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include "spreadsheet.hpp"

#include <iostream>

int main (int argc, const char * argv[])
{ 
    using namespace spreadsheet;

    Spreadsheet sheet;

    Cell<double> a = sheet.NewCell<double>("a");
    Cell<double> b = sheet.NewCell<double>("b");
    Cell<double> c = sheet.NewCell<double>("c");
    Cell<double> d = sheet.NewCell<double>("d");
    Cell<double> e = sheet.NewCell<double>("e");
    Cell<double> f = sheet.NewCell<double>("f");
    
    c.Set(SQRT(a()*a() + b()*b()));
    a.Set(3.0);
    b.Set(4.0);
    d.Set(c()+b());
    e.Set(d()+c());
    a.Set( SQRT(2 * b()) );
    b.Set(18.3);
    
    std::cout << " a=" << a.Value() 
              << " b=" << b.Value() 
              << " c=" << c.Value() 
              << " d=" << d.Value() 
              << " e=" << e.Value() 
              << std::endl;
    
    c.Set(a());

    std::cout << " a=" << a.Value() 
              << " b=" << b.Value() 
              << " c=" << c.Value() 
              << " d=" << d.Value() 
              << " e=" << e.Value() 
              << std::endl;

    
    std::cout << "Goodbye!\n";
    
    return 0;
}

