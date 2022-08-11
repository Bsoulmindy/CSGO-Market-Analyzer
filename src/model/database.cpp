#include <list>
#include "../class/Collection.hpp"
#include "../class/Case.hpp"
#include "database.hpp"
#include <sqlite3.h>
#include <iostream>
#include <cstring>
#include "../class/Weapon_Skin_Rarity.hpp"
#include "../class/Combination.hpp"
#include "../class/Wear_Info.hpp"
#include <string>

static int add_collection_case(void *data, int argc, char **argv, char **azColName)
{
    Collection_Case collection = Collection_Case(atoi(argv[0]), argv[1]);

    // Creating the hiearchy of the collection
    get_rarities_of_collection_case(collection);

    ((std::list<Collection_Case> *)data)->push_back(collection);

    return 0;
}

std::list<Collection_Case> initialize_collections_and_cases()
{
    std::list<Collection_Case> collections;
    sqlite3 *db;
    char *zErrMsg = 0;

    int rc = sqlite3_open("../data/database.db", &db);
    if (rc)
    {
        std::cout << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Can't open database database.db");
    }

    std::string sql = "SELECT id, name, type FROM Collection_Case";
    rc = sqlite3_exec(db, sql.c_str(), add_collection_case, &collections, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        std::cout << "SQL Error : " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }

    if (sqlite3_close(db) != SQLITE_OK)
        throw std::runtime_error("Error occured when closing database");
    return collections;
}

void get_rarities_of_collection_case(Collection_Case &collection_case)
{
    int id_collection = collection_case.get_id();
    sqlite3 *db;
    char *zErrMsg = 0;

    int rc = sqlite3_open("../data/database.db", &db);
    if (rc)
    {
        std::cout << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Can't open database database.db");
    }

    std::string sql = "SELECT id, rarity FROM Weapon_Skin_Rarity WHERE collection_case_idref = ?";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_bind_int(stmt, 1, id_collection);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW)
    {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    while (rc == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        Rarity rarity = static_cast<Rarity>(sqlite3_column_int(stmt, 1));
        Weapon_Skin_Rarity weapon_skin_rarity = Weapon_Skin_Rarity(id, rarity);

        get_skins_of_rarity(weapon_skin_rarity);

        collection_case.add_rarity(weapon_skin_rarity);
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    if (sqlite3_close(db) != SQLITE_OK)
        throw std::runtime_error("Error occured when closing database");
}

void get_rarities_of_case(Case &case_skins)
{
    int id_case = case_skins.get_id();
    sqlite3 *db;
    char *zErrMsg = 0;

    int rc = sqlite3_open("../data/database.db", &db);
    if (rc)
    {
        std::cout << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Can't open database database.db");
    }

    std::string sql = "SELECT id, rarity FROM Weapon_Skin_Rarity WHERE collection_idref = ?";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, NULL);
    if (rc != SQLITE_OK)
        throw std::runtime_error(sqlite3_errmsg(db));

    sqlite3_bind_int(stmt, 1, id_case);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW)
        throw std::runtime_error(sqlite3_errmsg(db));

    while (rc == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        Rarity rarity = static_cast<Rarity>(sqlite3_column_int(stmt, 1));
        Weapon_Skin_Rarity weapon_skin_rarity = Weapon_Skin_Rarity(id, rarity);

        get_skins_of_rarity(weapon_skin_rarity);

        case_skins.add_rarity(weapon_skin_rarity);
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    if (sqlite3_close(db) != SQLITE_OK)
        throw std::runtime_error("Error occured when closing database");
}

void get_skins_of_rarity(Weapon_Skin_Rarity &rarity)
{
    int id_rarity = rarity.get_id();
    sqlite3 *db;
    char *zErrMsg = 0;

    int rc = sqlite3_open("../data/database.db", &db);
    if (rc)
    {
        std::cout << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Can't open database database.db");
    }

    std::string sql = "SELECT id, name, wear_min, wear_max FROM Weapon_Skin WHERE rarity_idref = ?";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, NULL);
    if (rc != SQLITE_OK)
        throw std::runtime_error(sqlite3_errmsg(db));

    sqlite3_bind_int(stmt, 1, id_rarity);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW)
        throw std::runtime_error(sqlite3_errmsg(db));

    while (rc == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        std::string name = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
        float wear_min = sqlite3_column_double(stmt, 2);
        float wear_max = sqlite3_column_double(stmt, 3);
        Weapon_Skin weapon_skin = Weapon_Skin(id, name, wear_min, wear_max);

        get_wears_of_skin(weapon_skin);

        rarity.add_skin(weapon_skin);
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    if (sqlite3_close(db) != SQLITE_OK)
        throw std::runtime_error("Error occured when closing database");
}

void get_wears_of_skin(Weapon_Skin &skin)
{
    int id_skin = skin.get_id();
    sqlite3 *db;
    char *zErrMsg = 0;

    int rc = sqlite3_open("../data/database.db", &db);
    if (rc)
    {
        std::cout << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Can't open database database.db");
    }

    std::string sql = "SELECT id, wear, link FROM Weapon_Skin_Wear WHERE weapon_skin_idref = ?";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, NULL);
    if (rc != SQLITE_OK)
        throw std::runtime_error(sqlite3_errmsg(db));

    sqlite3_bind_int(stmt, 1, id_skin);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW)
        throw std::runtime_error(sqlite3_errmsg(db));

    while (rc == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        Wear wear = static_cast<Wear>(sqlite3_column_int(stmt, 1));
        std::string link = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
        Weapon_Skin_Wear weapon_wear = Weapon_Skin_Wear(id, wear, link);
        skin.add_wear(weapon_wear);
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    if (sqlite3_close(db) != SQLITE_OK)
        throw std::runtime_error("Error occured when closing database");
}

void save_combination(Combination const &combination)
{
    sqlite3 *db;
    char *zErrMsg = 0;

    int rc = sqlite3_open("../data/database.db", &db);
    if (rc)
    {
        std::cout << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Can't open database database.db");
    }

    std::string sql = "INSERT INTO Profitable_Combination (profit_margin, money_lost_in_worst_case) VALUES (?, ?)";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, NULL);
    if (rc != SQLITE_OK)
        throw std::runtime_error(sqlite3_errmsg(db));

    sqlite3_bind_double(stmt, 1, combination.get_profit_margin());
    sqlite3_bind_double(stmt, 2, combination.get_money_lost_in_worst_case());
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
        throw std::runtime_error(sqlite3_errmsg(db));

    sqlite3_finalize(stmt);
    // get id of combination
    sql = "select seq from sqlite_sequence where name = 'Profitable_Combination'";
    sqlite3_stmt *stmt2;
    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt2, NULL);
    if (rc != SQLITE_OK)
        throw std::runtime_error("SQL Error : Can't prepare statement (Profitable_Combination still exists)");

    rc = sqlite3_step(stmt2);
    if (rc != SQLITE_ROW)
        throw std::runtime_error("SQL Error : Can't step statement (Profitable_Combination still exists)");

    int id_combination = sqlite3_column_int(stmt2, 0);

    sqlite3_finalize(stmt2);

    for (auto const &input : combination.get_inputs())
    {
        sqlite3_stmt *stmt3;
        sql = "INSERT INTO Wear_Profit_Asso (combination_idref, wear_idref, is_input, wear_max, wear_min, price_max) VALUES (?, ?,?,?,?,?)";
        rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt3, NULL);
        if (rc != SQLITE_OK)
        {
            combination_rollback(id_combination);
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        sqlite3_bind_int(stmt3, 1, id_combination);
        sqlite3_bind_int(stmt3, 2, input.get_weapon_skin_wear().get_id());
        sqlite3_bind_int(stmt3, 3, 0);
        sqlite3_bind_double(stmt3, 4, input.get_wear_interval().get_max());
        sqlite3_bind_double(stmt3, 5, input.get_wear_interval().get_min());
        sqlite3_bind_double(stmt3, 6, input.get_price_max());

        rc = sqlite3_step(stmt3);
        if (rc != SQLITE_DONE)
        {
            combination_rollback(id_combination);
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt3);
    }

    for (auto const &output : combination.get_outputs())
    {
        sqlite3_stmt *stmt3;
        sql = "INSERT INTO Wear_Profit_Asso (combination_idref, wear_idref, is_input, wear_max, wear_min, price_max) VALUES (?, ?,?,?,?,?)";
        rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt3, NULL);
        if (rc != SQLITE_OK)
        {
            combination_rollback(id_combination);
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        sqlite3_bind_int(stmt3, 1, id_combination);
        sqlite3_bind_int(stmt3, 2, output.get_weapon_skin_wear().get_id());
        sqlite3_bind_int(stmt3, 3, 1);
        sqlite3_bind_double(stmt3, 4, 0.0f);
        sqlite3_bind_double(stmt3, 5, 0.0f);
        sqlite3_bind_int(stmt3, 6, 0.0f);

        rc = sqlite3_step(stmt3);
        if (rc != SQLITE_DONE)
        {
            combination_rollback(id_combination);
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt3);
    }

    if (sqlite3_close(db) != SQLITE_OK)
        throw std::runtime_error("Error occured when closing database");
}

static void combination_rollback(int id_combination)
{
    sqlite3 *db;
    char *zErrMsg = 0;

    int rc = sqlite3_open("../data/database.db", &db);
    if (rc)
    {
        std::cout << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Can't open database database.db");
    }

    std::string sql = "DELETE FROM Wear_Profit_Asso WHERE combination_idref = ?";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, NULL);
    if (rc != SQLITE_OK)
        throw std::runtime_error(sqlite3_errmsg(db));

    sqlite3_bind_int(stmt, 1, id_combination);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        std::cout << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sql = "DELETE FROM Profitable_Combination WHERE id = ?";
    sqlite3_stmt *stmt2;
    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt2, NULL);
    if (rc != SQLITE_OK)
        throw std::runtime_error(sqlite3_errmsg(db));

    sqlite3_bind_int(stmt2, 1, id_combination);
    rc = sqlite3_step(stmt2);
    if (rc != SQLITE_DONE)
        throw std::runtime_error(sqlite3_errmsg(db));

    sqlite3_finalize(stmt);
    sqlite3_finalize(stmt2);
    if (sqlite3_close(db) != SQLITE_OK)
        throw std::runtime_error("Error occured when closing database");
}

std::list<Wear_Info> get_profitation_of_wear(Weapon_Skin_Wear &wear)
{
    int id_wear = wear.get_id();

    sqlite3 *db;
    char *zErrMsg = 0;

    int rc = sqlite3_open("../data/database.db", &db);
    if (rc)
    {
        std::cout << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Can't open database database.db");
    }

    std::string sql = "SELECT wear_min, wear_max, price_max FROM Wear_Profit_Asso WHERE wear_idref = ?";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, NULL);
    if (rc != SQLITE_OK)
        throw std::runtime_error(sqlite3_errmsg(db));

    sqlite3_bind_int(stmt, 1, id_wear);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE && rc != SQLITE_ROW)
        throw std::runtime_error(sqlite3_errmsg(db));

    std::list<Wear_Info> infos;

    while (rc == SQLITE_ROW)
    {
        float wear_min = sqlite3_column_double(stmt, 0);
        float wear_max = sqlite3_column_double(stmt, 1);
        float price_max = sqlite3_column_double(stmt, 2);
        Interval interval(wear_min, wear_max);
        Wear_Info info(interval, price_max);

        infos.push_back(info);
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    if (sqlite3_close(db) != SQLITE_OK)
        throw std::runtime_error("Error occured when closing database");

    return infos;
}

void combination_rollback()
{
    sqlite3 *db;
    char *zErrMsg = 0;

    int rc = sqlite3_open("../data/database.db", &db);
    if (rc)
    {
        std::cout << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Can't open database database.db");
    }

    std::string sql = "select seq from sqlite_sequence where name = 'Profitable_Combination'";
    sqlite3_stmt *stmt2;
    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt2, NULL);
    if (rc != SQLITE_OK)
        throw std::runtime_error("SQL Error : Can't prepare statement (Profitable_Combination still exists)");

    rc = sqlite3_step(stmt2);
    if (rc != SQLITE_ROW)
        throw std::runtime_error("SQL Error : Can't step statement (Profitable_Combination still exists)");

    int id_combination = sqlite3_column_int(stmt2, 0);
    sqlite3_finalize(stmt2);
    if (sqlite3_close(db) != SQLITE_OK)
        throw std::runtime_error("Error occured when closing database");
    combination_rollback(id_combination);
}

std::list<Weapon_Skin_Wear> get_all_profitable_wears()
{
    sqlite3 *db;
    char *zErrMsg = 0;

    int rc = sqlite3_open("../data/database.db", &db);
    if (rc)
    {
        std::cout << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Can't open database database.db");
    }
    std::list<int> ids;
    std::string sql = "SELECT wear_idref FROM Wear_Profit_Asso WHERE is_input = 0";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, NULL);
    if (rc != SQLITE_OK)
        throw std::runtime_error(sqlite3_errmsg(db));
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE && rc != SQLITE_ROW)
        throw std::runtime_error(sqlite3_errmsg(db));
    while (rc == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        ids.push_back(id);
        rc = sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);

    std::list<Weapon_Skin_Wear> wears;

    for (int id : ids)
    {
        sql = "SELECT wear, link FROM Weapon_Skin_Wear WHERE id = ?";
        sqlite3_stmt *stmt2;
        rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt2, NULL);
        if (rc != SQLITE_OK)
            throw std::runtime_error(sqlite3_errmsg(db));

        sqlite3_bind_int(stmt2, 1, id);
        rc = sqlite3_step(stmt2);
        if (rc != SQLITE_DONE && rc != SQLITE_ROW)
            throw std::runtime_error(sqlite3_errmsg(db));
        while (rc == SQLITE_ROW)
        {
            Wear wear_type = (Wear)sqlite3_column_int(stmt2, 0);
            std::string link = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));

            Weapon_Skin_Wear wear(id, wear_type, link);
            wears.push_back(wear);

            rc = sqlite3_step(stmt2);
        }
        sqlite3_finalize(stmt2);
    }

    if (sqlite3_close(db) != SQLITE_OK)
        throw std::runtime_error("Error occured when closing database");

    return wears;
}

Collection_Case get_collection_case(int id)
{
    std::list<Collection_Case> collections;
    sqlite3 *db;
    char *zErrMsg = 0;

    int rc = sqlite3_open("../data/database.db", &db);
    if (rc)
    {
        std::cout << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Can't open database database.db");
    }

    std::string sql = "SELECT id, name, type FROM Collection_Case WHERE id = " + std::to_string(id);
    sqlite3_stmt *stmt;
    rc = sqlite3_exec(db, sql.c_str(), add_collection_case, &collections, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        std::cout << "SQL Error : " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }

    if (sqlite3_close(db) != SQLITE_OK)
        throw std::runtime_error("Error occured when closing database");
    return *(collections.begin());
}

Weapon_Skin_Wear find_by_id(int id)
{
    sqlite3 *db;
    char *zErrMsg = 0;

    int rc = sqlite3_open("../data/database.db", &db);
    if (rc)
    {
        std::cout << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Can't open database database.db");
    }
    std::string sql = "SELECT wear, link FROM Weapon_Skin_Wear WHERE id = " + std::to_string(id);
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, NULL);
    if (rc != SQLITE_OK)
        throw std::runtime_error(sqlite3_errmsg(db));
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE && rc != SQLITE_ROW)
        throw std::runtime_error(sqlite3_errmsg(db));
    if (rc == SQLITE_ROW)
    {
        Wear wear_type = (Wear)sqlite3_column_int(stmt, 0);
        std::string link = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));

        Weapon_Skin_Wear wear(id, wear_type, link);
        sqlite3_finalize(stmt);
        if (sqlite3_close(db) != SQLITE_OK)
            throw std::runtime_error("Error occured when closing database");
        return wear;
    }
    sqlite3_finalize(stmt);
    if (sqlite3_close(db) != SQLITE_OK)
        throw std::runtime_error("Error occured when closing database");
    throw std::runtime_error("No weapon skin found with id " + std::to_string(id));
}

int check_if_combination_outputs_are_the_same(Combination &combination)
{
    sqlite3 *db;
    char *zErrMsg = 0;

    int rc = sqlite3_open("../data/database.db", &db);
    if (rc)
    {
        std::cout << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Can't open database database.db");
    }

    std::set<int> combination_ids_set;
    std::set<int> combination_ids_set_tmp;
    bool isFirstOutput = true;

    for (Combination_Output output : combination.get_outputs())
    {
        std::string sql = "SELECT combination_idref FROM Wear_Profit_Asso WHERE is_input = 1 AND wear_idref = " + std::to_string(output.get_weapon_skin_wear().get_id());
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, NULL);
        if (rc != SQLITE_OK)
            throw std::runtime_error(sqlite3_errmsg(db));
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE && rc != SQLITE_ROW)
            throw std::runtime_error(sqlite3_errmsg(db));
        if (rc == SQLITE_DONE)
        {
            sqlite3_finalize(stmt);
            if (sqlite3_close(db) != SQLITE_OK)
                throw std::runtime_error("Error occured when closing database");
            return 0;
        }
        while (rc == SQLITE_ROW)
        {
            int combination_idref = sqlite3_column_int(stmt, 0);
            if (isFirstOutput)
            {
                combination_ids_set.insert(combination_idref);
            }
            else
            {
                if (combination_ids_set.find(combination_idref) != combination_ids_set.end())
                {
                    combination_ids_set_tmp.insert(combination_idref);
                }
            }
            rc = sqlite3_step(stmt);
        }
        sqlite3_finalize(stmt);

        if (!isFirstOutput)
        {
            combination_ids_set.clear();
            combination_ids_set = combination_ids_set_tmp;
            combination_ids_set_tmp.clear();
            if (combination_ids_set.size() == 0)
            {
                if (sqlite3_close(db) != SQLITE_OK)
                    throw std::runtime_error("Error occured when closing database");
                return 0;
            }
        }
        isFirstOutput = false;
    }

    if (sqlite3_close(db) != SQLITE_OK)
        throw std::runtime_error("Error occured when closing database");

    // Normally, the database shouldn't have 2 combinations with the same outputs
    for (int id_combination : combination_ids_set)
    {
        return id_combination;
    }
    return 0;
}

void insert_input_in_combination(int id_combination, Combination_Input combination_input)
{
    sqlite3 *db;
    char *zErrMsg = 0;

    int rc = sqlite3_open("../data/database.db", &db);
    if (rc)
    {
        std::cout << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Can't open database database.db");
    }

    // Check if there's already an input
    std::string sql = "SELECT wear_idref FROM Wear_Profit_Asso WHERE is_input = 0 AND combination_idref = " + std::to_string(id_combination) + " AND wear_idref = " + std::to_string(combination_input.get_weapon_skin_wear().get_id());
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, NULL);
    if (rc != SQLITE_OK)
        throw std::runtime_error(sqlite3_errmsg(db));
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE && rc != SQLITE_ROW)
        throw std::runtime_error(sqlite3_errmsg(db));
    if (rc == SQLITE_ROW)
    {
        std::string sql = "UPDATE Wear_Profit_Asso SET wear_max = " +
                          std::to_string(combination_input.get_wear_interval().get_max()) +
                          ", wear_min = " + std::to_string(combination_input.get_wear_interval().get_min()) +
                          ", price_max = " + std::to_string(combination_input.get_price_max()) +
                          " WHERE combination_idref = " + std::to_string(id_combination) +
                          " AND wear_idref = " + std::to_string(combination_input.get_weapon_skin_wear().get_id()) +
                          " AND is_input = 0 ";
        rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &zErrMsg);
        if (rc != SQLITE_OK)
        {
            std::cout << "SQL Error : " << zErrMsg << std::endl;
            sqlite3_free(zErrMsg);
        }
    }
    else if (rc == SQLITE_DONE) // If there's already
    {
        std::string sql = "INSERT INTO Wear_Profit_Asso (is_input, combination_idref, wear_idref, wear_max, wear_min, price_max) VALUES (0, " + std::to_string(id_combination) + ", " + std::to_string(combination_input.get_weapon_skin_wear().get_id()) + ", " + std::to_string(combination_input.get_wear_interval().get_max()) + ", " + std::to_string(combination_input.get_wear_interval().get_min()) + ", " + std::to_string(combination_input.get_price_max()) + ")";
        rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &zErrMsg);
        if (rc != SQLITE_OK)
        {
            std::cout << "SQL Error : " << zErrMsg << std::endl;
            sqlite3_free(zErrMsg);
        }
    }
    sqlite3_finalize(stmt);
    if (sqlite3_close(db) != SQLITE_OK)
        throw std::runtime_error("Error occured when closing database");
}