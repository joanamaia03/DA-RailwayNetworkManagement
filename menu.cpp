#include "menu.h"

menu::menu() {}

void menu::minTrainMenu() {
    int sec_choice;
    do {
        graph.reset();
        minTrainDisplay();
        sec_choice = readInteger("Selecione a opcao: ");
        switch(sec_choice){
            case 1: {
                Vertex *a = readVertex("Selecione a estacao de partida: ");
                if (a == nullptr) break;
                Vertex *b = readVertex("Selecione a estacao de chegada: ");
                if (b == nullptr) break;

                int res = graph.maxTrains(a->getName(), b->getName());
                cout << "\nResultado: " << res << '\n';
                break;
            }
            case 2: {
                Vertex *a = readVertex("Selecione a estacao de partida: ");
                if (a == nullptr) break;
                Vertex *b = readVertex("Selecione a estacao de chegada: ");
                if (b == nullptr) break;

                int res = graph.minCost(a->getName(), b->getName());
                cout << "\nResultado: " << res << '\n';
                break;
                
            }
            case 3: {
                Vertex *a = readVertex("Selecione a estacao de partida: ");
                if (a == nullptr) break;
                Vertex *b = readVertex("Selecione a estacao de chegada: ");
                if (b == nullptr) break;

                while (true) {
                    Edge *selectedEdge = readEdge("Selecione um edge: ");
                    if (selectedEdge == nullptr) break;
                    selectedEdge->setAvailable(false);
                }
                
                int res = graph.maxTrains(a->getName(), b->getName());
                cout << "\nResultado: " << res << '\n';
                break;
            }
            default:
                break;
        }
    }
    while(sec_choice!=4);
}

void menu::mainMenu() {
    int choice;
    do {
        menuDisplay();
        choice = readInteger("Selecione a opcao: ");
        switch(choice){
            case 1: {
                minTrainMenu();
                break;
            }
            case 2: {
                std::vector<std::pair<string,string>> max = graph.MaxFlowFullRail();
                break;
            }
            case 3: {
                int x;
                cout <<
                        "  1: distritos\n"
                        "  2: municipios\n"
                        "Selecione a opcao:\n";
                cin>>x;
                vector<pair<string, int>> result;
                int k = 10;
                result = graph.assignBudgets(k, x);
                for (int i = 0; i < result.size(); i++) {
                    cout << result[i].first << " - "<<result[i].second<<'\n';
                }
                break;
            }
            case 4: {
                Vertex *a = readVertex("Selecione a estacao de partida: ");
                if (a == nullptr) break;
                double d = graph.MaxFlowSpecificStat(a->getName());
                cout << "Numero maximo de comboios: " << d;
                break;
            }
            case 5: {
                while (true) {
                    Edge *selectedEdge = readEdge("Selecione um edge: ");
                    if (selectedEdge == nullptr) break;
                    selectedEdge->setAvailable(false);
                }
                int k=readInteger("Insira o numero: ");
                vector<string> result;
                result = graph.affectedStations(k);
                for(int i = 0; i < result.size(); i++){
                    cout << result[i] <<'\n';
                }
                break;
            }
            default:
                break;

        }
    }
    while(choice!=6);
}

int menu::readInteger(string prompt) {
    int result;
    cout << '\n' << prompt;
    cin >> result;
    return result;
}

string menu::readString(string prompt) {
    string result;
    cout << '\n' << prompt;
    getline(cin >> ws, result);

    return result;
}

Vertex *menu::readVertex(string prompt) {
    string read = readString(prompt);
    if (!graph.vertexExists(read)) {
        cout << "Vertex \"" << read << "\" nao existe!\n";
        return nullptr;
    }
    return graph.getVertex(read);
}

Edge *menu::readEdge(string prompt) {
    cout << prompt <<'\n';
    Vertex *a = readVertex("Selecione a 1a estacao: ");
    if (a == nullptr) return nullptr;
    cout << "Selecione uma das estacoes abaixo para a desabilitar:\n";
    for (Edge *e : a->getEdgesOut()) {
        //if (!e->isAvailable()) continue;
        cout << "* " << e->getStationB()->getName() << '\n';
    }

    Vertex *b = readVertex("Selecione a 2a estacao: ");
    if (b == nullptr) return nullptr;
    for (Edge *e : a->getEdgesOut())
        if (e->getStationB() == b) return e;
    
    cout << "O edge selecionado nao existe\n";
    return nullptr;
}


void menu::menuDisplay(){
    cout<<  "                                    Menu\n"
        "---------------------------------------------------------------------------------------\n"
        "1: Numero maximo de comboios entre duas estacoes\n"
        "2: Estacoes que requerem mais comboios\n"
        "3: Top-k dos municicipios e distritos  relativamente as suas necessidades de transporte\n"
        "4: Numero maximo de comboios numa determinada estacao\n"
        "5: Top-k das estacoes mais afetadas para cada segmento\n"
        "6: Sair\n";
}

void menu::minTrainDisplay() {
    cout<<  "                             Menu\n"
            "-----------------------------------------------------------------\n"
            "1: Numero maximo de comboios entre duas estacoes\n"
            "2: Numero maximo de comboios entre duas estacoes com custo minimo\n"
            "3: Numero maximo de comboios entre duas estacoes em rede reduzida\n"
            "4: Voltar ao menu principal\n";
}
