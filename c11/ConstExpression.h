//
constexpr int get_five() {return 5;} 


void ConstExpression()
{   
    int some_value[get_five() + 7];
	
    constexpr double earth_gravitational_acceleration = 9.8;
    constexpr double moon_gravitational_acceleration = earth_gravitational_acceleration / 6.0;	    
}