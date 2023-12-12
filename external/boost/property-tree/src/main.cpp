#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/program_options.hpp>

#include <fstream>
#include <iostream>
#include <iomanip>

namespace pt = boost::property_tree;
namespace po = boost::program_options;

using ptype = pt::ptree::path_type;
using namespace std;

static const char *JSON_OUT_FILENAME = "./out.json";

int main() {
    ofstream out{JSON_OUT_FILENAME};
    out << R"(
        {
            "a" : {
                "b" : {
                    "c" : "1825",
                    "d" : "I gonna cum"
                }
            }
        }
    )" << endl;
    out.close();

    pt::ptree root;
    pt::read_json(JSON_OUT_FILENAME, root);


    ptype jsonpath_c("a|b|c", '|');
    ptype jsonpath_d("a|b|d", '|');

    auto c = root.get<int>(jsonpath_c);
    auto d = root.get<string>(jsonpath_d);

    cout << "c : 0x" << hex << setfill('0') << setw(4) << c << endl;
    cout << "d : " << d << endl;

    return 0;
}
