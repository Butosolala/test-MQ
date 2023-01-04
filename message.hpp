#include <boost/serialization/string.hpp>
#include <boost/serialization/access.hpp>


class info
{
    public:
        info (int i = 0, std::string n = "")
            : number(i), text(n)
        {};

        int number;
        std::string text;

    private:
        friend class boost::serialization::access;

        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {  
                ar & number;
                ar & text;
            }
};