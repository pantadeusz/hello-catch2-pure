#include "catch.hpp"

#include "database.hpp"
#include <iostream>
using Catch::Matchers::Contains;

TEST_CASE("simple database object crud test", "[db]") {
  SECTION("create database object") {
    REQUIRE_NOTHROW([]() { database_c<int> database; });
  }
  SECTION("get all from empty database") {
    database_c<int> database;
    CHECK(database.get_all().size() == 0);
  }
}

TEST_CASE("advanced database object crud test", "[db][advanced]") {
  database_c<int> database;
  database.data_["0"] = 123;
  database.data_["1"] = 124;
  database.data_["2"] = 127;

  SECTION("get all from database with 3 objects inside") {
    CHECK(database.get_all().size() == 3);
  }

  SECTION("is data correct") {
    CHECK(database.get_all() == std::list<int>{123, 124, 127});
  }

  SECTION("we should be able to remove data from collection") {
      REQUIRE_NOTHROW(database.remove("0"));
      REQUIRE_THROWS(database.remove("0"));
      REQUIRE_THROWS_WITH(database.remove("0"),Contains("not exist"));
  }
}

struct person_t {
  int age;
  std::string name;
};

std::ostream &operator<<(std::ostream &out, const person_t l) {
  out << "{ age: " << l.age << ", name: " << l.name << "}";
  return out;
}
bool operator==( const person_t &l,const person_t &r) {
    return l.age == r.age && l.name == r.name;
}

SCENARIO("database operations") {
  database_c<person_t> database;

  GIVEN("database contains 2 values") {
    database.data_["0"] = {90, "Gertruda"};
    database.data_["1"] = {95, "Gerwazy"};
    WHEN("Eliza is added to database") {
      person_t p = {20, "Eliza"};
      database.put("3", p);
      THEN("the database should contain 3 values") {
        CHECK(database.get_all().size() == 3);
      }
      THEN("Eliza is added on the last index") {
        REQUIRE(database.get_all().back().name == "Eliza");
      }
      THEN("other values are not changed") {
        REQUIRE_THAT(database.get_all().front().name, Contains("Ger"));
      }
      THEN("last value is exactly the same as expected") {
        REQUIRE(database.get_all().back() == p);
      }
    }
  }
}
