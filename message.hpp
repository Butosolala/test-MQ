#include <boost/serialization/string.hpp>
#include <boost/serialization/access.hpp>


class info
{
    public:
        info (int i = 0, std::string n = "")
            : id(i), name(n)
        {};

        int id;
        std::string name;

    private:
        friend class boost::serialization::access;

        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {  
                ar & id;
                ar & name;
            }
};