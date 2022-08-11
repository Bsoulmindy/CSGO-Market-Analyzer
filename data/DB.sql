CREATE TABLE Collection_Case(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    type INTEGER -- 0: collection, 1: case
);

CREATE TABLE Weapon_Skin_Rarity(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    rarity INTEGER,
    collection_case_idref INTEGER, -- 0: Consumer grade, 1: Industrial grade, 2: Mil-Spec, 3: Restricted, 4: Classified, 5: Covert, 6: Contreband
    FOREIGN KEY(collection_case_idref) REFERENCES Collection_Case(id)
);

CREATE TABLE Weapon_Skin(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    wear_min REAL,
    wear_max REAL,
    rarity_idref INTEGER,
    FOREIGN KEY(rarity_idref) REFERENCES Weapon_Skin_Rarity(id)
);

CREATE TABLE Weapon_Skin_Wear(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    wear INTEGER, -- 0:Factory New, 1:Minimal Wear, 2:Field-Tested, 3:Well-Worn, 4:Battle-Scarred
    link TEXT,
    weapon_skin_idref INTEGER,
    FOREIGN KEY(weapon_skin_idref) REFERENCES Weapon_Skin(id)
);

CREATE TABLE Profitable_Combination(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    profit_margin REAL,
    money_lost_in_worst_case REAL
);

CREATE TABLE Wear_Profit_Asso(
    combination_idref INTEGER,
    wear_idref INTEGER,
    is_input INTEGER, -- 0: input, 1: output
    wear_max REAL DEFAULT 0.0,
    wear_min REAL DEFAULT 0.0,
    price_max REAL DEFAULT 0.0,
    FOREIGN KEY(combination_idref) REFERENCES Profitable_Combination(id),
    FOREIGN KEY(wear_idref) REFERENCES Weapon_Skin_Wear(id),
    PRIMARY KEY(combination_idref, wear_idref)
);