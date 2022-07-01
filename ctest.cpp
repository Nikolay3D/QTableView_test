#include "ctest.h"
#include <QRandomGenerator>

QStringList randow_words = {
    "jinnah",
    "kisumu",
    "mendel",
    "sweden",
    "adonic",
    "albify",
    "almost",
    "almous",
    "anodic",
    "aquose",
    "avowed",
    "behowl",
    "belled",
    "bunter",
    "carman",
    "cetene",
    "charuk",
    "chetty",
    "chwana",
    "citrus",
    "coking",
    "colima",
    "creole",
    "cygnus",
    "deltic",
    "dodger",
    "dokhma",
    "dorado",
    "dotage",
    "dudish",
    "engage",
    "ensand",
    "enwood",
    "feijoa",
    "fencer",
    "fitted",
    "frasco",
    "gainer",
    "gamine",
    "gaviae",
    "gayish",
    "genapp",
    "gnaeus",
    "graped",
    "hylism",
    "inhume",
    "inseer",
    "insist",
    "jerald",
    "jugate",
    "kerana",
    "lansat",
    "latten",
    "lauric",
    "leader",
    "lochia",
    "loungy",
    "lunula",
    "marang",
    "markab",
    "marler",
    "minima",
    "mnesic",
    "motyka",
    "multum",
    "nebris",
    "nonoic",
    "oecist",
    "onrush",
    "oolong",
    "ostomy",
    "paraph",
    "parian",
    "primal",
    "pulsar",
    "rashti",
    "roncet",
    "selina",
    "shakha",
    "shoofa",
    "sialis",
    "sitkan",
    "smooch",
    "snaily",
    "spleet",
    "starry",
    "sundik",
    "thwart",
    "tinned",
    "trashy",
    "tropic",
    "tusser",
    "tutman",
    "uncity",
    "unduly",
    "unhide",
    "unslit",
    "upwith",
    "uracil",
    "wedger",
};

CTest::CTest()
{

}

QVector<CUserObj> CTest::generate_data()
{
    QVector<CUserObj> out;

    int num_obj = 15;
    int num_keys = 20;

    for(int i = 1; i <= num_obj; ++i){
        CUserObj tmp(QString("Obj %1").arg(i));

        // add unique key
        if(QRandomGenerator::global()->bounded(1,num_obj) == i){
            QString key = randow_words.at(QRandomGenerator::global()->bounded(0,randow_words.size()));
            tmp.append(key, CUserData(randow_words.at(QRandomGenerator::global()->bounded(0,randow_words.size())), false));
        }

        for(int j = 1; j <= num_keys; ++j){
            int val_type = QRandomGenerator::global()->bounded(TCell::TCELL_NONE,TCell::TCELL_NUM);
            QString key = QString("Key %1").arg(j, 2, 10, QLatin1Char('0'));
            QVariant val = QVariant();
            bool empty = QRandomGenerator::global()->generate() % 2 == 0 ? true : false;
            switch (val_type) {
                case TCell::TCELL_DOUBLE:
                    val = QRandomGenerator::global()->generateDouble();
                    tmp.append(key, CUserData(empty ? double(0.0) : val, empty));
                break;
                case TCell::TCELL_BOOL:
                    val = QRandomGenerator::global()->generate() % 2 == 0 ? true : false;
                    tmp.append(key, CUserData(empty ? false : val, empty));
                break;
                case TCell::TCELL_STR:
                    val = QString("Str_%1").arg(QRandomGenerator::global()->bounded(0,1000));
                    tmp.append(key, CUserData(empty ? "" : val, empty));
                break;
                default:
                    //no value
                break;
            }

        }

        out.append(tmp);
    }

    return out;
}
