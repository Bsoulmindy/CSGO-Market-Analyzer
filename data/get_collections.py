# this pyton file is needed to get the SQL code for the database
import requests
from bs4 import BeautifulSoup

id_last_collection = 36
id_last_rarity = 168
id_last_skin = 509


def get_rarity(div, rarities, skin_rarity_dict):
    text = div.find('p', class_='nomargin').text
    if(div.find('h3').find_all('a').__len__() == 1):
        return
    name = div.find('h3').find_all('a')[0].text
    name += " | "
    name += div.find('h3').find_all('a')[1].text
    if 'Consumer' in text:
        if rarities.count(0) == 0:
            rarities.append(0)
        skin_rarity_dict[name] = 0
    if 'Industrial' in text:
        if rarities.count(1) == 0:
            rarities.append(1)
        skin_rarity_dict[name] = 1
    if 'Mil-Spec' in text:
        if rarities.count(2) == 0:
            rarities.append(2)
        skin_rarity_dict[name] = 2
    if 'Restricted' in text:
        if rarities.count(3) == 0:
            rarities.append(3)
        skin_rarity_dict[name] = 3
    if 'Classified' in text:
        if rarities.count(4) == 0:
            rarities.append(4)
        skin_rarity_dict[name] = 4
    if 'Covert' in text:
        if rarities.count(5) == 0:
            rarities.append(5)
        skin_rarity_dict[name] = 5


def create_rarity_dict(rarity_dict, rarities):
    global id_last_rarity
    for rarity in rarities:
        id_last_rarity += 1
        rarity_dict[rarity] = id_last_rarity


def change_to_rarity_idref(skin_rarity_dict, rarities_dict):
    for skin, rarity in skin_rarity_dict.items():
        skin_rarity_dict[skin] = rarities_dict[rarity]


def write_collection_and_rarities(rarities_dict, name_collection, collection_or_case):
    global id_last_collection
    id_last_collection += 1
    f = open('data/result.sql', 'a')
    f.write('INSERT INTO Collection_Case(id, name, type) VALUES(' +
            str(id_last_collection) + ',\"' + name_collection + '\",' + str(collection_or_case) + ');\n')
    for key, value in rarities_dict.items():
        f.write('INSERT INTO Weapon_Skin_Rarity(id, rarity, collection_case_idref) VALUES(' +
                str(value) + ',' + str(key) + ',' + str(id_last_collection) + ');\n')
    f.close()


def write_wears(name, min, max, rarity_idref):
    list = []
    if(min < 0.07):
        list.append(0)
    if(min < 0.15 and max > 0.07):
        list.append(1)
    if(min < 0.38 and max > 0.15):
        list.append(2)
    if(min < 0.45 and max > 0.38):
        list.append(3)
    if(max > 0.45):
        list.append(4)

    link = name.replace(' ', '%20')

    global id_last_skin
    id_last_skin += 1

    f = open('data/result.sql', 'a')
    f.write('INSERT INTO Weapon_Skin(id, name, rarity_idref, wear_min, wear_max) VALUES(' +
            str(id_last_skin) + ',\"' + name + '\",' + str(rarity_idref) + ',' + str(min) + ',' + str(max) + ');\n')

    for wear in list:
        url = link
        if(wear == 0):
            url += '%20(Factory%20New)'
        if(wear == 1):
            url += '%20(Minimal%20Wear)'
        if(wear == 2):
            url += '%20(Field-Tested)'
        if(wear == 3):
            url += '%20(Well-Worn)'
        if(wear == 4):
            url += '%20(Battle-Scarred)'

        f = open('data/result.sql', 'a')
        f.write('INSERT INTO Weapon_Skin_Wear(wear, link, weapon_skin_idref) VALUES(' +
                str(wear) + ', \"' + url + '\",' + str(id_last_skin) + ');\n')
        f.close()


def main(line, collection_or_case):
    splits = line.split('/')
    collection_name = splits[len(
        splits) - 1].replace('+', ' ').replace('\n', '').replace('-', ' ')
    r = requests.get(line.replace('\n', ''))
    parsed_html = BeautifulSoup(r.text, 'html.parser')
    for souvenir in parsed_html.find_all('div', class_='row collection-souvenir-coolapsable content-header-collapseable'):
        souvenir.extract()
    rarities = []
    skin_rarity_dict = {}
    for div in parsed_html.find_all('div', class_='col-lg-4 col-md-6 col-widen text-center'):
        get_rarity(div, rarities, skin_rarity_dict)
    rarities.sort()
    rarities_dict = {}
    create_rarity_dict(rarities_dict, rarities)
    change_to_rarity_idref(skin_rarity_dict, rarities_dict)
    write_collection_and_rarities(
        rarities_dict, collection_name, collection_or_case)

    # Getting weapon_skins
    for div in parsed_html.find_all('div', class_='col-lg-4 col-md-6 col-widen text-center'):
        h3 = div.find('h3')
        if (h3.find_all('a').__len__() == 1):
            continue
        name = h3.find_all('a')[0].text
        name += " | "
        name += h3.find_all('a')[1].text
        price = div.find('div', class_='price')
        p = price.find('p')
        if p.find('a', class_='price-souv') is None:
            r2 = requests.get(p.find('a')['href'])
            parsed_html2 = BeautifulSoup(r2.text, 'html.parser')
            min = float(parsed_html2.find_all(
                'div', class_='marker-value cursor-default')[0].text)
            max = float(parsed_html2.find_all(
                'div', class_='marker-value cursor-default')[1].text)
            write_wears(name, min, max, skin_rarity_dict[name])


# with open("data/collections.txt") as file:
#     for line in file:
#         main(line, 0)

with open("data/cases.txt") as file:
    for line in file:
        main(line, 1)
