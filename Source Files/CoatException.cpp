#include "CoatException.h"

CoatException::CoatException(const string& message) : message{ message }
{
}

string CoatException::get_message() const
{
    return this->message;
}

CoatValidator::CoatValidator(const Controller& controller) : controller{ controller }
{
}

void CoatValidator::validate_add(const Coat& c)
{
    string errors;
    if (!this->controller.valid_coat(c))
        errors += "Invalid coat, it already exists!\n";
    if (errors.size() > 0)
        throw CoatException(errors);
}

void CoatValidator::validate_remove(string search_size, string search_colour, string search_photograph)
{
    string errors;
    Coat c{ search_size, search_colour, 1, 1, search_photograph };
    if (this->controller.valid_coat(c))
        errors += "This coat doesn't exist!\n";
    if (errors.size() > 0)
        throw CoatException(errors);
}

//void CoatValidator::validate_update(string search_size, string search_colour, string search_photograph)
//{
//    string errors;
//    Coat c{ search_size, search_colour, 1, 1, search_photograph };
//    if (!this->controller.valid_coat(c))
//        errors += "The coat you wanted to remove doesn't exist!\n";
//    if (errors.size() > 0)
//        throw CoatException(errors);
//}

