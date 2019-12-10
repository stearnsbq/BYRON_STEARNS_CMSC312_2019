#include "programfilegenerator.h"
#include <time.h>
#include <vector>

programfilegenerator::programfilegenerator()
{

    srand(time(nullptr));

}


QJsonDocument programfilegenerator::generate(int count){

    std::vector<QString> names = {"Text Processor", "Web Browser", "Video Game", "Chat"};
    std::vector<QString> instrs = {"CALCULATE", "I/O", "OUT", "YIELD", "CRITICAL_CALCULATE", "CRITICAL_IO"};
    QString instr;

    QJsonDocument doc;

    QJsonObject obj;
    QJsonArray instructions;
    QJsonObject instruction;


    int runtime = 0;
    int critical = 0;
    for(int i = 0; i < count; i++) {
        QString it;

        if(critical == 0) {
            it = instrs.at(rand() % 6);
            if(it.contains("CRITICAL")) {
                critical++;
            }
        }else{
            it = instrs.at(rand() % 4);
        }



        int rt = (rand() % 75 + 1);
        if(it == "CALCULATE" || it == "CRITICAL_CALCULATE") {
            runtime += rt;
        }else if(it == "OUT") {
            instruction.insert("Out", names.at(rand()% 4) );
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
    critical = 0;
    return doc;
}
