#include "programfilegenerator.h"
#include <time.h>
#include <vector>

programfilegenerator::programfilegenerator()
{

    srand(time(nullptr));

}


QJsonDocument programfilegenerator::generate(int count){

    std::vector<QString> names = {"Text Processor", "Web Browser", "Video Game", "Chat"};
    std::vector<QString> instrs = {"CALCULATE", "I/O", "OUT"};
    QString instr;

    QJsonDocument doc;

    QJsonObject obj;
    QJsonArray instructions;
    QJsonObject instruction;


    int runtime = 0;
    int c = (rand() % 50) + 1;
    for(int i = 0; i < c; i++) {

        QString it = instrs.at(rand() % 2);
        int rt = (rand() % 75 + 1);
        if(it == "CALCULATE") {
            runtime += rt;
        }else if(it == "OUT") {
            it += names.at(rand()% 4);
        }

        instruction.insert("Type", it);
        instruction.insert("Burst", rt);
        instructions.append(instruction);
        instruction = QJsonObject();
    }

    obj.insert("instructions", instructions);
    obj.insert("Name", names.at(rand() % 4));
    obj.insert("Runtime", runtime);
    obj.insert("Memory", rand() % 4096 + 1);



    doc.setObject(obj);

    return doc;
}
