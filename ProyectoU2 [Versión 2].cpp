#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

const int maxLevel = 100;

class Villages {
private:
    vector<vector<int>> adjacencyMatrix;
    unordered_map<string, int> vertexIndices;

public:
    void addVertex(const string& vertex) {
        if (vertexIndices.find(vertex) == vertexIndices.end()) {
            int index = vertexIndices.size();
            vertexIndices[vertex] = index;
            for (vector<int>& row : adjacencyMatrix) {
                row.resize(index + 1);
            }
            adjacencyMatrix.resize(index + 1, vector<int>(index + 1));
        }
    }

    void addEdge(const string& vertex1, const string& vertex2) {
        if (vertexIndices.find(vertex1) == vertexIndices.end() || vertexIndices.find(vertex2) == vertexIndices.end()) {
            cout << "Uno o ambos vertices no existen." << endl;
            return;
        }

        int index1 = vertexIndices[vertex1];
        int index2 = vertexIndices[vertex2];
        adjacencyMatrix[index1][index2] = 1;
        adjacencyMatrix[index2][index1] = 1;
    }

    void addEdgeWithWeight(const string& vertex1, const string& vertex2, int weight) {
        if (vertexIndices.find(vertex1) == vertexIndices.end() || vertexIndices.find(vertex2) == vertexIndices.end()) {
            cout << "Uno o ambos vertices no existen." << endl;
            return;
        }

        int index1 = vertexIndices[vertex1];
        int index2 = vertexIndices[vertex2];
        adjacencyMatrix[index1][index2] = weight;
        adjacencyMatrix[index2][index1] = weight;
    }

    void printAdjacencyMatrix() {
        for (const vector<int>& row : adjacencyMatrix) {
            for (int value : row) {
                cout << value << " ";
            }
            cout << endl;
        }
    }

    void printVertexIndices() {
        for (const auto& entry : vertexIndices) {
            cout << entry.first << ": " << entry.second << endl;
        }
    }
};

class Guardian {
private:
    string name;
    int powerLevel;
    string mainMaster;
    string village;
    bool isMaster;

public:
    Guardian(const string& name, int powerLevel, const string& mainMaster, const string& village)
        : name(name), powerLevel(powerLevel), mainMaster(mainMaster), village(village), isMaster(false) {}

    void printInfo() const {
        cout << "Nombre: " << name << endl;
        cout << "Nivel de poder: " << powerLevel << endl;
        cout << "Maestro principal: " << mainMaster << endl;
        cout << "Aldea: " << village << endl;
        cout << "Estado: " << (isMaster ? "Maestro" : "Aprendiz") << endl;
        cout << endl;
    }

    string getName() const {
        return name;
    }

    string getMainMaster() const {
        return mainMaster;
    }

    void setIsMaster(bool value) {
        isMaster = value;
    }
};

class Guardians {
private:
    unordered_map<string, vector<Guardian>> guardiansByVillage;

public:
    void addGuardian(const string& village, const string& name, int powerLevel, const string& mainMaster) {
	    if (powerLevel > maxLevel) {
	        cout << "El nivel de poder del guardian '" << name << "' excede el limite maximo permitido." << endl;
	        return;
	    }
	
	    guardiansByVillage[village].emplace_back(name, powerLevel, mainMaster, village);
	}

    void printGuardiansByVillage() {
        for (const auto& entry : guardiansByVillage) {
            const string& village = entry.first;
            const vector<Guardian>& guardians = entry.second;

            cout << "Aldea: " << village << endl;
            cout << "Cantidad de guardianes: " << guardians.size() << endl;

            for (const Guardian& guardian : guardians) {
                guardian.printInfo();
            }

            cout << "--------------------------------------------------" << endl;
        }
    }
    
    void checkGuardianStatus() {
	    for (auto& entry : guardiansByVillage) {
	        vector<Guardian>& guardians = entry.second;
	
	        for (Guardian& guardian : guardians) {
	            bool isMaster = false;
	
	            for (const auto& entry2 : guardiansByVillage) {
	                const vector<Guardian>& otherGuardians = entry2.second;
	
	                for (const Guardian& otherGuardian : otherGuardians) {
	                    if (otherGuardian.getMainMaster() == guardian.getName()) {
	                        isMaster = true;
	                        break;
	                    }
	                }
	
	                if (isMaster) {
	                    break;
	                }
	            }
	
	            if (isMaster) {
	                guardian.setIsMaster(true);
	            } else {
	                guardian.setIsMaster(false);
	            }
	        }
	    }
	}
};

int main() {

    Villages graph;
    Guardians guardians;

    ifstream file("Villages.csv");
    if (file) {
        string line;
        getline(file, line);
        while (getline(file, line)) {
            stringstream ss(line);
            string village1, village2;
            getline(ss, village1, ',');
            getline(ss, village2, ',');
            graph.addVertex(village1);
            graph.addVertex(village2);
            graph.addEdge(village1, village2);
        }
        file.close();

    } else {
        cout << "Error al abrir el archivo Villages.csv." << endl;
    }

    ifstream file2("Guardians.csv");
	if (file2) {
	    string line;
	    getline(file2, line);
	    while (getline(file2, line)) {
	        stringstream ss(line);
	        string name, powerLevelStr, mainMaster, village;
	        getline(ss, name, ',');
	        getline(ss, powerLevelStr, ',');
	        getline(ss, mainMaster, ',');
	        getline(ss, village, ',');
	
	        int powerLevel = stoi(powerLevelStr);
	
	        graph.addVertex(village);
	        guardians.addGuardian(village, name, powerLevel, mainMaster);
	    }
	    file2.close();
	
	    guardians.checkGuardianStatus();
	
	    //graph.printAdjacencyMatrix();
	
	    //cout << "\nOrden de las villas:\n";
	    //graph.printVertexIndices();
	
	    //cout << "\nGuardianes por aldea:\n";
	    //guardians.printGuardiansByVillage();
	} else {
	    cout << "Error al abrir el archivo Guardians.csv." << endl;
	}

    // Presentación y sinopsis del juego
    cout << "******************************************************************** The Guardian Journey ******************************************************************" << endl;


    cout << "\t\t\t\t    En un mundo devastado por la guerra y la lucha constante existen los Guardianes. Los" << endl
         << "\t\t\t\t\t\t\t\t        Guardianes son heroes con habilidades y destrezas unicas que protegen a las aldeas a lo" << endl
         << "\t\t\t\t    largo de toda la tierra siendo estas los ultimos asentamientos de la humanidad." << endl << endl
         << "\t\t\t\t    Tesla es la capital de estas tierras y hoy corresponde a un farol en la oscuridad donde" << endl
         << "\t\t\t\t    abunda la prosperidad, el desarrollo tecnologico y entregan la mayor proteccion a lo largo" << endl
         << "\t\t\t\t    del nuevo mundo." << endl << endl
         << "\t\t\t\t    Cada ser humano tiene un poder interior que le permite definir su destino y elegir en una" << endl
         << "\t\t\t\t    de las cuatro facciones que existen hoy en dia, las cuales son; magos, vikingos," << endl
         << "\t\t\t\t    nigromantes y bestias. En ocasiones existen humanos con la posibilidad de desarrollar" << endl
         << "\t\t\t\t    habilidades de mas de una faccion lo que les permite ser grandes candidatos a recibir el" << endl
         << "\t\t\t\t    titulo de guardianes." << endl << endl
         << "\t\t\t\t    A los alrededores de Tesla se encuentran las aldeas que corresponden a asentamientos" << endl
         << "\t\t\t\t\t\t\t\t        que cumplen distintas funciones dentro de la gran organizacion de la humanidad y en cada" << endl
         << "\t\t\t\t    una de estas aldeas existen maestros, quienes ensenan las artes de los guardianes." << endl<< endl
         << "\t\t\t\t    El sueno de cada nino es convertirse en un Guardian y ganar el torneo, pero el viaje de un" << endl
         << "\t\t\t\t    aprendiz no es facil y su destino depende de las decisiones que tome a lo largo de este" << endl
         << "\t\t\t\t    recorrido." << endl << endl;

    cout << "\t\t\t\t    ";

    system("pause");

    return 0;

}
