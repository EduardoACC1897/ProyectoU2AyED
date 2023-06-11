#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <list>

using namespace std;

// Variable general de nivel maximo
const int maxLevel = 100;

// Clase aldeas
class Villages {
private:
    vector<vector<int>> adjacencyMatrix;
    unordered_map<string, int> vertexIndices;

public:
	// Función para añadir al unordered_map las aldea desde el archivo
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
	
	// Función para añadir a la matriz las conexiones entre las aldea desde el archivo
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
	
	// Función para imprimir la matriz
    void printAdjacencyMatrix() {
        for (const vector<int>& row : adjacencyMatrix) {
            for (int value : row) {
                cout << value << " ";
            }
            cout << endl;
        }
    }
	
	// Función para imprimir el unordered_map de la aldea
    void printVertexIndices() {
        for (const auto& entry : vertexIndices) {
            cout << entry.first << ": " << entry.second << endl;
        }
    }
    
    // Función para imprimir las conexiones entre las aldeas
    void printVillageConnections() {
	    for (const auto& entry : vertexIndices) {
	        const string& village = entry.first;
	        int index = entry.second;
	
	        cout << "\t\t\t\t    " << village << ": ";
	        for (int i = 0; i < adjacencyMatrix[index].size(); i++) {
	            if (adjacencyMatrix[index][i] != 0) {
	                for (const auto& vertexEntry : vertexIndices) {
	                    if (vertexEntry.second == i) {
	                        cout << vertexEntry.first << " ";
	                        break;
	                    }
	                }
	            }
	        }
	        cout << endl;
	    }
	}
	
	// Función para viajar entre las aldeas
	string selectCityToTravel(const string& playerVillage, bool prepared, const string& bossVillage) {
	    string destination;
	    cout << "\t\t\t\t    Ingrese el nombre de la ciudad a la que desea viajar: ";
	    cin.ignore();
	    getline(cin, destination);
	    
	
	    while (true) {
	        // Verificar si el destino es válido en el grafo
	        auto it = vertexIndices.find(playerVillage);
	        if (it == vertexIndices.end()) {
	            cout << "\t\t\t\t    La aldea del jugador no existe en el grafo." << endl;
	            destination = "";  // Reiniciar el valor de destination
	        } else {
	            int playerIndex = it->second;
	            it = vertexIndices.find(destination);
	            if (it == vertexIndices.end()) {
	                cout << "\t\t\t\t    El destino no existe en el grafo." << endl;
	                destination = "";  // Reiniciar el valor de destination
	            } else {
	                int destinationIndex = it->second;
	
	                // Verificar si el destino está conectado a la aldea del jugador
	                if (playerVillage != destination && adjacencyMatrix[playerIndex][destinationIndex] == 0) {
	                    cout << "\t\t\t\t    No hay una conexion directa entre las ciudades seleccionadas." << endl;
	                    destination = "";  // Reiniciar el valor de destination
	                } else if (destination == bossVillage && !prepared) {
	                    // Verificar si el destino es la ciudad del jefe y no se puede viajar en este momento
	                    cout << "\t\t\t\t    No puedes viajar a la ciudad del jefe en este momento." << endl;
	                    destination = "";  // Reiniciar el valor de destination
	                } else if (destination == playerVillage) {
	                    // Verificar si el destino es el mismo que la aldea del jugador
	                    cout << "\t\t\t\t    El destino no puede ser el mismo que la aldea del jugador." << endl;
	                    destination = "";  // Reiniciar el valor de destination
	                } else {
	                    // Todas las validaciones pasaron, se retorna el destino
	                    return destination;
	                }
	            }
	        }
	
	        // Volver a solicitar el nombre de la ciudad
	        cout << "\t\t\t\t    Ingrese el nombre de la ciudad a la que desea viajar: ";
	        getline(cin, destination);
	    }
	}
	
	// Función para determinar si el unordered_map que recibe tiene todas las aldeas menos 1
	bool hasAllVillages(const unordered_map<string, int>& allowPoints) {
	    int expectedSize = vertexIndices.size() - 1;
	    int actualSize = allowPoints.size();
	
	    return (actualSize == expectedSize);
	}
	
	// Función para realizar alquimia y crear un camino entre las aldeas
	int alchemy(const string& playerVillage, bool prepared, const string& bossVillage) {
	    string destination;
	    cout << "\t\t\t\t    Ingrese el nombre de la ciudad a la que desea viajar: ";
	    cin.ignore();
	    getline(cin, destination);
		while (true) {
	
	        // Verificar si el destino es válido en el grafo
	        auto itPlayer = vertexIndices.find(playerVillage);
	        auto itDestination = vertexIndices.find(destination);
	
	        if (itPlayer == vertexIndices.end()) {
	            cout << "\t\t\t\t    La aldea del jugador no existe en el grafo." << endl;
	            destination = "";  // Reiniciar el valor de destination
	        } else if (itDestination == vertexIndices.end()) {
	            cout << "\t\t\t\t    El destino no existe en el grafo." << endl;
	            destination = "";  // Reiniciar el valor de destination
	        } else if (destination == bossVillage) {
	            if (!prepared) {
	                cout << "\t\t\t\t    No puedes crear un camino hacia la ciudad del jefe en este momento." << endl;
	                destination = "";  // Reiniciar el valor de destination
	            } else {
	                addEdge(playerVillage, destination);
	                cout << "\t\t\t\t    Se ha creado un camino entre las aldeas " << playerVillage << " y " << destination << "." << endl;
	                return (rand() % 3) + 2;
	            }
	        } else {
	            addEdge(playerVillage, destination);
	            cout << "\t\t\t\t    Se ha creado un camino entre las aldeas " << playerVillage << " y " << destination << "." << endl;
	            return (rand() % 3) + 2;
	        }
	        
	        // Volver a solicitar el nombre de la ciudad
	        cout << "\t\t\t\t    Ingrese el nombre de la ciudad a la que desea viajar: ";
	        getline(cin, destination);
	    }
	}
};

// Clase guardian
class Guardian {
private:
    string name;
    int powerLevel;
    string mainMaster;
    string village;
    bool isMaster;
    int chosen;

public:
    Guardian(const string& name, int powerLevel, const string& mainMaster, const string& village)
    : name(name), powerLevel(powerLevel), mainMaster(mainMaster), village(village), isMaster(false), chosen(0) {}
    
    Guardian(const string& name, int powerLevel, const string& mainMaster, const string& village, int chosen)
    : name(name), powerLevel(powerLevel), mainMaster(mainMaster), village(village), isMaster(false), chosen(chosen) {}
	
	// Función para imprimir los datos de los guardianes
    void printInfo() const {
	    cout << "Nombre: " << name << endl;
	    cout << "Nivel de poder: " << powerLevel << endl;
	    cout << "Maestro principal: " << mainMaster << endl;
	    cout << "Aldea: " << village << endl;
	    cout << "Rol: " << (isMaster ? "Maestro" : "Aprendiz") << endl;
	    cout << "Elegido: " << chosen << endl;
	    cout << endl;
	}

    string getName() const {
        return name;
    }
    
    int getPowerLevel() const {
        return powerLevel;
    }

    string getMainMaster() const {
        return mainMaster;
    }

    void setIsMaster(bool value) {
        isMaster = value;
    }
    
    bool getIsMaster() const {
        return isMaster;
    }
    
    string getVillage() const {
        return village;
    }
    
    void setChosen(int value) {
        chosen = value;
    }
    
    void setPowerLevel(int value) {
        powerLevel = value;
    }
    
    int getChosen() const {
		return chosen;
	}
    
};

// Clase guardianes
class Guardians {
private:
    unordered_map<string, vector<Guardian>> guardiansByVillage;

public:
	// Función para añadir al unordered_map los guardianes del archivo
    void addGuardian(const string& village, const string& name, int powerLevel, const string& mainMaster) {
	    if (powerLevel > maxLevel) {
	        cout << "El nivel de poder del guardian '" << name << "' excede el limite maximo permitido." << endl;
	        return;
	    }
	
	    guardiansByVillage[village].emplace_back(name, powerLevel, mainMaster, village);
	}
	
	// Función para añadir el guardian creado por el jugador
	void addGuardianPlayer(const string& village, const string& name, int powerLevel, const string& mainMaster, int chosen) {
	    if (powerLevel > maxLevel) {
	        cout << "El nivel de poder del guardian '" << name << "' excede el limite maximo permitido." << endl;
	        return;
	    }
	
	    guardiansByVillage[village].emplace_back(name, powerLevel, mainMaster, village, chosen);
	}
	
	// Función para imprimir los guardianes por aldea
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
    
    // Función para imprimir los guardianes aprendices
    void printApprenticeGuardiansByVillage() {
	    for (const auto& entry : guardiansByVillage) {
	        const string& village = entry.first;
	        const vector<Guardian>& guardians = entry.second;
	
	        for (const Guardian& guardian : guardians) {
	            if (!guardian.getIsMaster()) {
	                cout << "\t\t\t\t    Nombre: " << guardian.getName() << endl;
	                cout << "\t\t\t\t    Nivel de poder: " << guardian.getPowerLevel() << endl;
	                cout << "\t\t\t\t    Maestro principal: " << guardian.getMainMaster() << endl;
	                cout << "\t\t\t\t    Aldea: " << guardian.getVillage() << endl;
	                cout << "\t\t\t\t    Rol: " << (guardian.getIsMaster() ? "Maestro" : "Aprendiz") << endl;
	                cout << endl;
	                cout << "\t\t\t\t    --------------------------------------------------" << endl;
	                
	            }
	        }	        
	    }
	}
    
    // Función para vereficar los roles de los guardianes y establecerlos
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
	
	// Función para determinar donde esta el guardian de mayor nivel
	bool hasMaxLevelGuardian(const string& village) const {
	    const vector<Guardian>& guardians = guardiansByVillage.at(village);
	    for (const Guardian& guardian : guardians) {
	        if (guardian.getPowerLevel() == maxLevel) {
	            return true;
	        }
	    }
	    return false;
	}
	
	// Función para imprimir aldeas menos la de que tiene el guardian de mayor nivel
	void printVillagesWithoutMaxLevelGuardian() {
	    for (const auto& entry : guardiansByVillage) {
	        const string& village = entry.first;
	        if (!hasMaxLevelGuardian(village)) {
	            cout << "\t\t\t\t    - " << village << endl;
	        }
	    }
	}
	
	// Función para si se encuentra la aldea
	bool isValidVillage(const string& village) const {
	    return guardiansByVillage.count(village) > 0;
	}
	
	// Función para que el jugador elija el guardian
	void chooseApprenticeGuardian(Guardians& guardians) {
	    bool guardianFound = false;
	
	    while (!guardianFound) {
	        cout << "\t\t\t\t    Ingrese el nombre del guardian que desea elegir: ";
	        string guardianName;
	        cin >> guardianName;
	
	        // Recorrer todos los guardianes por aldea
	        for (auto& entry : guardians.guardiansByVillage) {
	            vector<Guardian>& guardians = entry.second;
	
	            // Buscar el guardián de tipo aprendiz por nombre y cambiar chosen a 1
	            for (Guardian& guardian : guardians) {
	                if (!guardian.getIsMaster() && guardian.getName() == guardianName) {
	                    // Cambiar chosen a 1
	                    guardian.setChosen(1);
	                    
	                    // Actualizar el nivel del guardián a la mitad de maxLevel
	                    int newPowerLevel = maxLevel / 2;
	                    guardian.setPowerLevel(newPowerLevel);
	
	                    guardianFound = true;
	                    break;
	                }
	            }
	
	            if (guardianFound) {
	                break;
	            }
	        }
	
	        if (!guardianFound) {
	            cout << "\t\t\t\t    No se encontro ningun guardian aprendiz con ese nombre. Intentelo nuevamente." << endl;
	        }
	    }
	
	    cout << "\t\t\t\t    Guardian seleccionado exitosamente." << endl;
	}
	
	// Función para encontrar guardian del jugador
	void findChosenGuardian(const Guardians& guardians, string& playerName, int& playerPowerLevel, string& playerVillage) {
	    for (const auto& entry : guardians.guardiansByVillage) {
	        const vector<Guardian>& guardianList = entry.second;
	        
	        for (const Guardian& guardian : guardianList) {
	            if (guardian.getChosen() == 1) {
	                playerName = guardian.getName();
	                playerPowerLevel = guardian.getPowerLevel();
	                playerVillage = guardian.getVillage();
	                return;
	            }
	        }
	    }
	}
	
	// Función para encontrar el guardian de mayor nivel, que por lo tanto es el jefe final
	void assignBossGuardian(string& bossName, string& bossVillage) {
	    for (const auto& entry : guardiansByVillage) {
	        const vector<Guardian>& guardianList = entry.second;
	
	        for (const Guardian& guardian : guardianList) {
	            if (guardian.getPowerLevel() == maxLevel) {
	                bossName = guardian.getName();
	                bossVillage = guardian.getVillage();
	                return;
	            }
	        }
	    }
	}
	
	// Función para imprimir guardianes que esten en la misma aldea que el jugador
	void printGuardiansInThePlayersVillage(const string& playerVillage) const {
	    cout << "\t\t\t\t    |Guardianes en la aldea|" << endl << endl;
	    
	    const Guardian* recommendedGuardian = nullptr;
	    int lowestLevel = INT_MAX;
	
	    for (const auto& entry : guardiansByVillage) {
	        const string& aldea = entry.first;
	        const vector<Guardian>& guardianList = entry.second;
	
	        if (aldea == playerVillage) {
	            for (const Guardian& guardian : guardianList) {
	                if (guardian.getChosen() != 1) {
	                    cout << "\t\t\t\t    Nombre: " << guardian.getName() << endl;
	                    cout << "\t\t\t\t    Nivel de Poder: " << guardian.getPowerLevel() << endl;
	                    cout << "\t\t\t\t    Rol: " << (guardian.getIsMaster() ? "Maestro" : "Aprendiz") << endl << endl;
	                    
	                    if (guardian.getPowerLevel() < lowestLevel) {
	                        lowestLevel = guardian.getPowerLevel();
	                        recommendedGuardian = &guardian;
	                    }
	                }
	            }
	        }
	    }
	    
	    if (recommendedGuardian != nullptr) {
	        cout << "\t\t\t\t    *Recomendado para enfrentarse: " << recommendedGuardian->getName() << endl;
	        cout << "\t\t\t\t    *Nivel de Poder: " << recommendedGuardian->getPowerLevel() << endl << endl;
	    }
	}

    // Función para elegir el guardian con el que el jugador entranará
    void trainWithGuardian(const string& playerVillage, string& guardianTrainerName, int& guardianTrainerPowerLevel, string& guardianTrainerRol) {
	    string desiredGuardianName;
	    bool guardianFound = false;
	
	    while (!guardianFound) {
	        cout << "\t\t\t\t    Ingrese el nombre del guardian con el que desea entrenar: ";
	        cin >> desiredGuardianName;
	
	        for (const auto& entry : guardiansByVillage) {
	            const string& aldea = entry.first;
	            const vector<Guardian>& guardianList = entry.second;
	
	            if (aldea == playerVillage) {
	                for (const Guardian& guardian : guardianList) {
	                    if (guardian.getName() == desiredGuardianName && guardian.getChosen() != 1) {
	                        guardianTrainerName = guardian.getName();
	                        guardianTrainerPowerLevel = guardian.getPowerLevel();
	                        guardianTrainerRol = (guardian.getIsMaster() ? "Maestro" : "Aprendiz");
	                        guardianFound = true;
	                        break;
	                    }
	                }
	            }
	
	            if (guardianFound) {
	                break;
	            }
	        }
	
	        if (!guardianFound) {
	            cout << "\t\t\t\t    No se encontro ningun guardian con ese nombre en la misma aldea del jugador. Intente nuevamente." << endl;
	        }
	    }
	
	    if (!guardianFound) {
	        guardianTrainerName = "";
	        guardianTrainerPowerLevel = 0;
	        guardianTrainerRol = "";
	    }
	}
	
};

// Función para que el jugador eleja la aldea a la que pertenece si crea el guardian
string getValidVillage(const Guardians& guardians) {
    string village;
    bool isValid = false;
    
    cin.ignore();

    while (!isValid) {
        cout << "\t\t\t\t    Ingrese el nombre de la aldea: ";
        getline(cin, village);

        if (guardians.isValidVillage(village) && !guardians.hasMaxLevelGuardian(village)) {
            isValid = true;
        } else {
            cout << "\t\t\t\t    La aldea ingresada no es valida o ya tiene un guardian de nivel maximo. Por favor, intente nuevamente." << endl;
        }
    }

    return village;
}

// Función para imprimir lista del historial del combate
void printListsCombat(const list<string>& list1, const list<string>& list2) {
    auto it1 = list1.begin();
    auto it2 = list2.begin();

    while (it1 != list1.end() || it2 != list2.end()) {
        if (it1 != list1.end()) {
            cout << "\t\t\t\t    " << *it1;
            ++it1;
        }

        cout << " ---------------- [";

        if (it2 != list2.end()) {
            cout << *it2;
            ++it2;
        }

        cout << "]" << endl;
    } 
}

// Función para imprimir la lista del historial de viajes
void printListsTravel(const list<string>& list1, const list<string>& list2) {
    auto it1 = list1.begin();
    auto it2 = list2.begin();

    while (it1 != list1.end() || it2 != list2.end()) {
        if (it1 != list1.end()) {
            cout << "\t\t\t\t    " << *it1;
            ++it1;
        }

        cout << " ----------------> ";

        if (it2 != list2.end()) {
            cout << *it2;
            ++it2;
        }

        cout << endl;
    }
}

// Función para añadir al unordered_map las aldeas que el jugador visite
void addAllowPoints(unordered_map<string, int>& allowPoints, const string& playerVillage, int d) {
    auto it = allowPoints.find(playerVillage);
    if (it == allowPoints.end()) {
        allowPoints[playerVillage] = d;
    }
}

// Función para entregar un numero aleatorio entre 1 y 6
int rollDice() {
    int randomNumber = rand() % 6 + 1;
    return randomNumber;
}

// Función para asegurar que los puntos que el jugador puede ganar entrenando por aldea no superen a 3
int addToSecondVariable(unordered_map<string, int>& allowPoints, const string& playerVillage, int d) {
    auto it = allowPoints.find(playerVillage);
    if (it != allowPoints.end()) {
        int& secondVar = it->second;
        int currentSum = secondVar + d;
        int maxAllowed = 3 - secondVar;
        int finalSum = currentSum > 3 ? maxAllowed : d;
        secondVar += finalSum;
        return finalSum;
    }
    return 0;  // Clave no encontrada, no se realizó ninguna suma
}

int main() {

    Villages graph;
    Guardians guardians;
    string guardianName;
	
	// Lectura del archivo Villages.csv
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
	
	// Lectura del archivo Guardians.csv
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
    
    cout << endl;
	
	// Objetivo y reglas
	cout << "**************************************************************** Objetivos y reglas del juego **************************************************************" << endl << endl;
	
	cout << "\t\t\t\t\t\t\t\t     |Objetivo del juego|" << endl << endl
		 << "\t\t\t\t    Tomaras el control de un aprendiz de guardian o crearas uno, con el cual deberas recorrer" << endl
	     << "\t\t\t\t    las aldeas de un vasto mundo en busca de derrotar al guardian mas poderoso ubicado en Tesla." << endl << endl
	     << "\t\t\t\t    Para lograr este objetivo, tendras que subir de nivel a traves de entrenamientos con los" << endl
	     << "\t\t\t\t    aprendices o maestros guardianes de las distintas aldeas. Todo con el unico fin de llegar a ser" << endl
	     << "\t\t\t\t    lo suficientemente fuerte como para enfrentarte y derrotar al guardián en Tesla, y coronarte" << endl
	     << "\t\t\t\t    como el mas poderoso de todos." << endl << endl;
	     
	cout << "\t\t\t\t    ";

    system("pause");
    
    cout << endl;
    
    cout << "\t\t\t\t\t\t\t\t      |Reglas del juego|" << endl << endl
	     << "\t\t\t\t    *Sistema de nivel*:" << endl << endl
	     << "\t\t\t\t      - El nivel maximo permitido es 100." << endl
	     << "\t\t\t\t      - Tu guardian comenzara con un nivel equivalente al 50% del nivel maximo." << endl
	     << "\t\t\t\t      - Visitar una aldea otorgara a tu guardian 1 nivel." << endl
	     << "\t\t\t\t      - Superar un entrenamiento con un aprendiz de la aldea otorgara a tu guardian 1 nivel." << endl
	     << "\t\t\t\t      - Superar el entrenamiento con un maestro de la aldea otorgara a tu guardian 2 niveles." << endl
	     << "\t\t\t\t      - La cantidad maxima de niveles que se pueden obtener de entrenamientos por aldea es 3." << endl
	     << "\t\t\t\t      - Tu guardian se considerara preparado cuando alcance el 90% del nivel maximo." << endl << endl;
	
	cout << "\t\t\t\t    ";

    system("pause");
    
    cout << endl;
	
	cout << "\t\t\t\t    *Sistema de entrenamientos*:" << endl << endl
	     << "\t\t\t\t      - Los entrenamientos consistiran en una serie de pruebas que tu guardian debera superar." << endl
	     << "\t\t\t\t      - La cantidad minima de pruebas en un entrenamiento con un guardian aprendiz es de 3." << endl
	     << "\t\t\t\t      - La cantidad minima de pruebas en un entrenamiento con un guardian maestro es de 5." << endl
	     << "\t\t\t\t      - Se anadira 1 prueba adicional al entrenamiento por cada 10 niveles menos que tenga tu guardian con el que entrene." << endl
	     << "\t\t\t\t      - Cada prueba consistira en lanzar un dado y adivinar si el resultado es par o impar." << endl
	     << "\t\t\t\t      - La cantidad de veces que tendras que adivinar el resultado del dado es igual al numero de pruebas." << endl
	     << "\t\t\t\t      - Completaras las pruebas si logras adivinar correctamente el resultado del dado, de lo contrario las fallaras." << endl
	     << "\t\t\t\t      - Un entrenamiento se considerara superado si el numero de pruebas completadas es mayor al numero de pruebas falladas." << endl
	     << "\t\t\t\t      - De lo contrario, se considerara como fallado." << endl << endl;
    	 
	cout << "\t\t\t\t    ";

    system("pause");
    
    cout << endl;
    
    cout << "\t\t\t\t    *Sistema de viajes*:" << endl << endl
	     << "\t\t\t\t      - Tu guardian comenzara en la aldea que elegiste al crearlo o en la aldea que asignaste por defecto." << endl
	     << "\t\t\t\t      - Tu guardian podra viajar entre las distintas aldeas solo si estan conectadas entre si." << endl
	     << "\t\t\t\t      - Tu guardian se considerara preparado si logra visitar todas las aldeas excepto la aldea del Jefe." << endl
	     << "\t\t\t\t      - Para viajar a Tesla tu guardian debe considerarse preparado." << endl << endl;

	cout << "\t\t\t\t    ";
	
	system("pause");
	
	cout << endl;
	
	cout << "\t\t\t\t    *Sistema de alquimia*:" << endl << endl
	     << "\t\t\t\t      - Se te permitira utilizar el sistema de alquimia para crear caminos entre la aldea en la." << endl
	     << "\t\t\t\t        que te encuentras y otra, excepto Tesla si no estas prepado" << endl
	     << "\t\t\t\t      - Cada vez que utilices el sistema de alquimia, se reduciran entre 2 y 4 niveles de tu guardian." << endl << endl;
	
	cout << "\t\t\t\t    Recuerda tener en cuenta los sistemas anteriores y seguir las instrucciones que se te indiquen" << endl
	     << "\t\t\t\t    para asegurar el correcto funcionamiento del juego. Vamos a jugar!" << endl << endl;
    	 
	cout << "\t\t\t\t    ";

    system("pause");
    
    cout << endl;
    
    // Menu de inicio
	cout << "************************************************************************** Menu de inicio ******************************************************************" << endl << endl;
	
	cout << "\t\t\t\t    |Menu de inicio|" << endl << endl;
	
	// Pregunta al jugador si desea crear o elegir un guardián
	cout << "\t\t\t\t    Desea crear o elegir un guardian? (crear/elegir): ";
	string opcion;
	cin >> opcion;
	
	cout << endl;
	
	// Valida la opción ingresada por el jugador
	while (opcion != "crear" && opcion != "elegir") {
	    cout << "\t\t\t\t    Opcion invalida. Por favor, ingrese 'crear' o 'elegir': ";
	    cin >> opcion;
	    
	    cout << endl;
	}
	
	if (opcion == "crear") {
    // Solicita el nombre del guardián al jugador
	    cout << "\t\t\t\t    Ingrese el nombre del guardian: ";	    
	    cin >> guardianName;
	    cout << endl;
	
	    // Muestra las aldeas disponibles al jugador
	    cout << "\t\t\t\t    Aldeas disponibles:" << endl;
	    guardians.printVillagesWithoutMaxLevelGuardian();
	    cout << endl;
	
	    // Solicita la aldea del guardián al jugador
	    string village = getValidVillage(guardians);
	
	    // Crea el guardián con los datos ingresados por el jugador y lo agrega al resto de guardianes
	    guardians.addGuardianPlayer(village, guardianName, maxLevel / 2, "", 1);
	    
	    //guardians.printGuardiansByVillage();
	}
	
	if (opcion == "elegir") {
	    cout << "\t\t\t\t    Guardianes Aprendices por Aldea:" << endl;
	    cout << endl;
	    guardians.printApprenticeGuardiansByVillage();
	    cout << endl;
	    guardians.chooseApprenticeGuardian(guardians);
	    
	    //guardians.printGuardiansByVillage();
	    	    
	}
	
	cout << endl;
	
	// Comienzo del juego
	cout << "********************************************************************** Comienzo del juego ******************************************************************" << endl << endl;
	
	// variables que se usaran durante el juego
	int selectedOption;
	int testing;
	int a;
	int b;
	int c;
	int d = 0;
	int e;
	string travel;
	string evenOrOdd;
	int dice;
	int complete;
	bool validOption = false;
	
	string playerName;
    int playerPowerLevel;   
    string playerVillage;
    string playerRol;
	bool prepared = false;	
	
	string bossName;
	string bossVillage;
	
	string guardianTrainerName;
	int guardianTrainerPowerLevel;
	string guardianTrainerRol;
	
	guardians.findChosenGuardian(guardians, playerName, playerPowerLevel, playerVillage);
		
	guardians.assignBossGuardian(bossName, bossVillage);
	
	list<string> combatHistoryTrainer;
	list<string> combatHistoryResult;
	
	list<string> travelHistoryBegin;
	list<string> travelHistoryEnd;
	
	unordered_map<string, int> allowPoints;
	addAllowPoints(allowPoints, playerVillage, d);
	
	// While para que se desarrolle el juego mientras el jugador no venza al guardian de nivel mayor o boss
	while (playerRol != "Maestro") {
			
		cout << "\t\t\t\t    |Datos de tu guardian|" << endl << endl;
		cout << "\t\t\t\t    Nombre: " << playerName << endl;
		cout << "\t\t\t\t    Nivel de Poder: " << playerPowerLevel << endl;
		cout << "\t\t\t\t    Aldea: " << playerVillage << endl << endl;
		
		cout << "\t\t\t\t    |Acciones disponibles|" << endl << endl;
		cout << "\t\t\t\t    (1) Entrenar" << endl;
		cout << "\t\t\t\t    (2) Viajar" << endl;
		cout << "\t\t\t\t    (3) Alquimia" << endl << endl;
		
		// Validar opcion ingresada por el jugador
		while (!validOption) {
		    cout << "\t\t\t\t    Ingrese la opcion que desea realizar: ";
		    cin >> selectedOption;
		    cout << endl;
		
		    if (selectedOption >= 1 && selectedOption <= 3) {
		        validOption = true;
		    } else {
		        cout << "\t\t\t\t    Opcion invalida. Por favor, seleccione una opcion valida." << endl << endl;
		    }
		}
		
		validOption = false;
		
		// Entrenamiento
		if (selectedOption == 1) {
			
			a = 0;
			
			b = 0;
			
			c = 0;
			
			guardians.printGuardiansInThePlayersVillage(playerVillage);
			
			guardians.trainWithGuardian(playerVillage, guardianTrainerName, guardianTrainerPowerLevel, guardianTrainerRol);
					
			if (guardianTrainerRol == "Maestro") {				
				testing = 5;				
			} else {				
				testing = 3;				
			}
			
			cout << endl;
			
			cout << "\t\t\t\t    El entrenamiento con " << guardianTrainerName << " va a comenzar" << endl;
			
			if (playerPowerLevel < guardianTrainerPowerLevel) {
	            int levelDifference = guardianTrainerPowerLevel - playerPowerLevel;
	            int additionalTestingPoints = levelDifference / 10;
	            testing += additionalTestingPoints;
	            cout << endl;
	            cout << "\t\t\t\t    *Debido a vuestra diferencia de nivel tendras que resolver " << testing << " pruebas*" << endl;	            
	        }
	        
	        cout << endl;
	        
	        while (testing != a) {
			    dice = rollDice();        	
			    cout << "\t\t\t\t    Prueba " << a + 1 << ": Se ha lanzado un dado, crees que el resultado es par o impar?: ";
			    cin >> evenOrOdd;
			    
			    // Validar la entrada del usuario
			    while (evenOrOdd != "par" && evenOrOdd != "impar") {
			        cout << "\t\t\t\t    Entrada invalida. Por favor, ingrese 'par' o 'impar': ";
			        cin >> evenOrOdd;
			    }
			    
			    cout << endl;
			    
			    if (evenOrOdd == "par") {
			    	
			    	if (dice % 2 == 0) {			    		
			    		cout << "\t\t\t\t    Adivinaste el resultado del dado!" << endl << endl;
			    		b++;			    		
					} else {						
						cout << "\t\t\t\t    No adivinaste el resultado del dado" << endl << endl;
						c++;
					}
			    	
				} else {					
					if(dice % 2 != 0){						
						cout << "\t\t\t\t    Adivinaste el resultado del dado!" << endl << endl;			    		
			    		b++;						
					} else {						
						cout << "\t\t\t\t    No adivinaste el resultado del dado" << endl << endl;
						c++;						
					}
					
				}
			    
			    a++;
			}
			
			if(b > c){
				
				cout << "\t\t\t\t    Lograste superar el entrenamiento!" << endl << endl;
				
				combatHistoryTrainer.push_back(guardianTrainerName);
				combatHistoryResult.push_back("Superado");
				
				if(guardianTrainerName == bossName){
					
					playerRol = "Maestro";
					
				}
				
				if (guardianTrainerRol == "Maestro") {
					e = addToSecondVariable(allowPoints, playerVillage, 2);
					if (playerPowerLevel < maxLevel){
						playerPowerLevel += e;
					}									
					cout << "\t\t\t\t    Has sumado una cantidad de " << e << " puntos al nivel de poder de tu guardian" << endl;								
				} else {				
					e = addToSecondVariable(allowPoints, playerVillage, 1);					
					if (playerPowerLevel < maxLevel){
						playerPowerLevel += e;
					}
					cout << "\t\t\t\t    Has sumado una cantidad de " << e << " puntos al nivel de poder de tu guardian" << endl;				
				}
				
			}else{
				
				cout << "\t\t\t\t    No lograste superar la prueba" << endl;
				combatHistoryTrainer.push_back(guardianTrainerName);
				combatHistoryResult.push_back("Fallado");
				
			}
			
			cout << endl;
						
		}
		
		// Viaje
		if (selectedOption == 2) {
			
			cout << "\t\t\t\t    Aldeas y sus conecciones:" << endl << endl;
			
			graph.printVillageConnections();
			
			cout << endl;
			
			travel = graph.selectCityToTravel(playerVillage, prepared, bossVillage);
			
			travelHistoryBegin.push_back(playerVillage);
			travelHistoryEnd.push_back(travel);
			
			playerVillage = travel;
			
			addAllowPoints(allowPoints, playerVillage, d);
			
			if (playerPowerLevel < maxLevel) {				
				playerPowerLevel++;
			}
			
			cout << endl;
			
		}
		
		// Alquimia
		if (selectedOption == 3) {
			
			cout << "\t\t\t\t    Aldeas y sus conecciones:" << endl << endl;
			
			graph.printVillageConnections();
			
			cout << endl;
			
			playerPowerLevel -= graph.alchemy(playerVillage, prepared, bossVillage);
			
			cout << endl;
			
		}
		
		if (playerPowerLevel >= maxLevel * 0.9) {
		    
		    prepared = true;
		    
		}
		
		if(graph.hasAllVillages(allowPoints)){
			
			prepared = true;
			
		}
		
		if(playerRol != "Maestro"){
			
			cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
			
		}
		
	}
	
	// Final del juego
	cout << "******************************************************************* Historial final del juego **************************************************************" << endl << endl;
	
	// Estadisticas finales del jugador
	cout << "\t\t\t\t    |Estadisticas Jugador|" << endl << endl;
	
	cout << "\t\t\t\t    Nombre: " << playerName << endl;
	cout << "\t\t\t\t    Nivel de Poder: " << playerPowerLevel << endl;
	cout << "\t\t\t\t    Rol: " << playerRol << endl << endl;
	
	// Historial de combate
	cout << "\t\t\t\t    |Historial de combate|" << endl << endl;
	
	printListsCombat(combatHistoryTrainer, combatHistoryResult);
	
	cout << endl;
	
	// Historial de viajes
	cout << "\t\t\t\t    |Historial de viajes|" << endl << endl;
	
	printListsTravel(travelHistoryBegin, travelHistoryEnd);
	
    return 0;

}
