#include <iostream>
#include <fstream>
#include <climits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Grafo{
	private:	
		int** matrixAdj;
		int quantityOfNodes;
		vector<char> nodes;
		
	public:
		Grafo(int quantityOfNodes){
      this->quantityOfNodes = quantityOfNodes;
      createMatrix(quantityOfNodes);
    };

    void createMatrix(int quantityOfNodes) {
      matrixAdj = new int*[quantityOfNodes];

      for (int i=0; i<quantityOfNodes; i++) {
        matrixAdj[i] = new int[quantityOfNodes];
        for (int j=0; j<quantityOfNodes; j++) {
          matrixAdj[i][j] = 0;
                }
          }
            
		for (int i=0; i<quantityOfNodes; i++) {
			char c = 'A' + i;
			nodes.push_back(c);
		}
	}

    void addEdge(char origin, char destination, int w) {
	    matrixAdj[origin - 'A'][destination - 'A'] = w;
    }

    void loadMatrix() {
	    ifstream arch("aristas.txt");
	    string line;
	    int cont = 0, quantityOfNodes;
	
	  if (arch.fail()) {
		  cout<< "Error al abrir el archivo" <<endl;
		  return;
	  }
	
	  while (getline(arch, line)) {
		  istringstream stream(line);
		  char origin, destination;
		  int w;
		
		  if (cont != 0) {
			  stream >> origin;
			  while (stream.peek() == '-' || stream.peek() == '>') { stream.ignore(); }
			  stream >> destination >> w;
			  addEdge(origin, destination, w);
		  } 
		  cont++;	
	  }
	  arch.close();
  }

    int quantityOfNodesEdge() {
      ifstream arch("aristas.txt");
      int quantityOfNodes;
      
      if (arch.fail()) {
        cout<< "Error al abrir el archivo" <<endl;
        return 0;
      }
      
      arch >> quantityOfNodes;
      arch.close();
      return quantityOfNodes;
    }

    void printGrafo() {
      for (int origin=0; origin < (this->quantityOfNodes); origin++) {
        for (int destination=0; destination < (this->quantityOfNodes); destination++) {
          if (matrixAdj[origin][destination] != 0) {
            cout<< nodes[origin] << " -> " << nodes[destination] <<" Peso: "<< matrixAdj[origin][destination]<<endl;
          }
        }
      }
    }

    void deleteNode(char node) {
	int index = -1;
	
	for(int i=0; i<nodes.size(); i++){
		if (node == nodes[i]){
			index = i;
		}
	}
	
	if (index < 0 || index >= quantityOfNodes) {
		cout<<"El nodo no existe"<<endl;
		return;
	}
	
	for (int i=0; i<(this->quantityOfNodes); i++) {
		for (int j=index; j<(this->quantityOfNodes - 1); j++) {
			matrixAdj[i][j] = matrixAdj[i][j+1];
		}
	}
	
	for (int i=index; i<(this->quantityOfNodes - 1); i++) {
		for (int j=0; j<(this->quantityOfNodes); j++) {
			matrixAdj[i][j] = matrixAdj[i+1][j];
		}
	}
	
	this->quantityOfNodes = this->quantityOfNodes - 1;
	
	int** newMatrix = new int*[quantityOfNodes];
	for (int i=0; i<quantityOfNodes; i++) {
		newMatrix[i] = new int[quantityOfNodes];
	}
	
	for (int i=0; i<(this->quantityOfNodes); i++) {
		for (int j=0; j<(this->quantityOfNodes); j++) {
			newMatrix[i][j] = matrixAdj[i][j];
		}
	}
	
	for (int i=0; i<(this->quantityOfNodes + 1); i++) {
		delete[] matrixAdj[i];
	}
	delete[] matrixAdj;
	matrixAdj = newMatrix;
	
	nodes.erase(nodes.begin() + index);
}

  int** getMatrixAdj() {
    return matrixAdj;
  }

  vector<char> getNodes() {
    return nodes;
  }

  int getQuantityOfNodes() {
    return quantityOfNodes;
  }

};


int** warshall(int** matrixAdj, int quantityOfNodes, bool &conexo) {
	conexo = true;
	int** matrix = new int*[quantityOfNodes];
	
	for (int i=0; i<quantityOfNodes; i++) {
		matrix[i] = new int[quantityOfNodes];
		for (int j=0; j < quantityOfNodes; j++) {
			if (matrixAdj[i][j] != 0){
				matrix[i][j] = 1;	
			} else {
				matrix[i][j] = 0;
			}
		}
	}
	
	for(int node = 0; node < quantityOfNodes; node++) {
		for (int origin=0; origin < quantityOfNodes; origin++) {
			for (int destination=0; destination < quantityOfNodes; destination++) {
				matrix[origin][destination] = matrix[origin][destination] || (matrix[origin][node] && matrix[node][destination]);
			}
		}
	}
	
	for (int origin=0; origin < quantityOfNodes; origin++) {
		for (int destination=0; destination < quantityOfNodes; destination++) {
			if (origin != destination && (matrix[origin][destination] == 0 || matrix[destination][origin] == 0)){
				conexo = false;
			}
		}
	}
	
	if (quantityOfNodes == 1 && matrixAdj[0][0] == 0){
		conexo = false;
	}
	
	if (conexo) {
		cout<<"Es fuertemente conexo"<<endl;
	} else {
		cout<<"No es fuertemente conexo"<<endl;
	}
	
	return matrix;
}

void findSourcesAndSinks(int** matrixTrans, int quantityOfNodes, vector<char> nodes){
	bool exist = false;
	vector<int> isSources(quantityOfNodes, 1);
	vector<int> isSink(quantityOfNodes, 1);
	
	for (int i=0; i<quantityOfNodes; i++) {
		for (int j=0; j < quantityOfNodes; j++) {
			if (matrixTrans[i][j] != 0) {
				isSources[j]= 0;
				isSink[i] = 0;
			}
		}
	}
	
	cout<<"Nodos Fuente: ";
	for (int i=0; i<quantityOfNodes; i++) {
		if (isSources[i] == 1) {
			cout<<nodes[i]<<" ";
			exist = true;
		}
	}
	
	if (!exist) {
		cout<<"No existen nodos fuentos";
		exist = false;
	}
	
	cout<<"\nNodos Pozo: ";
	for (int i=0; i<quantityOfNodes; i++) {
		if(isSink[i] == 1){
			cout<<nodes[i]<<" ";
			exist = true;
		}
	}
	
	if (!exist) { cout<<"No existen nodos pozos"<<endl; }
}

void dijkstra(int** matrixAdj, vector<int> &distance, vector<bool> &visited, int quantityOfNodes) {
	for(int i=0; i<quantityOfNodes-1; i++){
		int nodeMin = -1;
		for(int j=0; j<quantityOfNodes; j++){
			if((nodeMin == -1 || distance[j] < distance[nodeMin]) && !visited[j]){
				nodeMin = j;
			}
		}
		
		visited[nodeMin] = true;
	
		for (int j=0; j<quantityOfNodes; j++){
			if(matrixAdj[nodeMin][j] != 0){
				int newDistance = distance[nodeMin] + matrixAdj[nodeMin][j];
				if(newDistance < distance[j] && !visited[j]) {
					distance[j] = newDistance;
					
				}
			}
		}	
	}
}

void findMinRoute(char originChar, char destinationChar, int quantityOfNodes, int** matrixAdj, int** matrixTrans, vector<char> nodes) {
	int origin = -1, destination = -1;
	
	for(int i=0; i<nodes.size(); i++){
		if (originChar == nodes[i]){
			origin = i;
		}
		if (destinationChar == nodes[i]){
			destination = i;
		}
	}
	
	if (origin < 0 || destination < 0 || origin >= quantityOfNodes  || destination >= quantityOfNodes) {
		cout<<"El nodo no existe"<<endl;
		return;
	}
	
	if (matrixTrans[origin][destination] == 0){
		cout<<"No existe un camino que lleve del nodo "<<nodes[origin]<<" hasta el nodo "<<nodes[destination]<<endl;
		return;
	}
	
	vector<int> distance(quantityOfNodes, INT_MAX);
	vector<bool> visited(quantityOfNodes, false);
	vector<int> route;
	
	int distanceLoop = 0;
	int lastDistance = 0;
	if (origin==destination) {
		route.push_back(destination);
		
		if (matrixAdj[origin][destination] != 0){
			distanceLoop = matrixAdj[origin][destination];
		}
		
		int cont = 0;
		int destination1 = destination;
		for (int i=0; i<quantityOfNodes; i++) {
			if ((matrixAdj[i][destination1] != 0 && cont == 0) || (matrixAdj[i][destination1] != 0 && matrixAdj[i][destination1] < lastDistance)){
				lastDistance = matrixAdj[i][destination1];
				destination = i;
				cont++;
			}
		}
	} 
	
	distance[origin] = 0;
	
	dijkstra(matrixAdj, distance, visited, quantityOfNodes);
	
	if (distance[destination]+lastDistance < distanceLoop || distanceLoop == 0){
		int node = destination;
		while(node != origin){
			route.push_back(node);
			for(int i=0; i<quantityOfNodes; ++i){
				if(matrixAdj[i][node] != 0 && distance[i] == (distance[node] - matrixAdj[i][node])){
					node = i;
					break;
				}
			}
		}
		route.push_back(origin);
		
		cout<<"La ruta minima es: ";
		for(int i=route.size()-1; i>=0; i--){
			cout<<nodes[route[i]];
			if(i!=0){
				cout<<" -> ";
			}
		}
		cout<<"\nEl peso minimo de esta ruta fue de: "<<distance[destination]+lastDistance<<endl;
		cout<<endl;
	} else {
		cout<<"El nodo "<<nodes[origin]<<" tiene un lazo, que es la ruta minima: "<<nodes[origin]<<" -> "<<nodes[origin]<<endl;
		cout<<"El peso minimo de esta ruta fue: "<<distanceLoop<<endl;
	}	
}

int main() {

		cout	<<"pasa por aqui: "<<endl;

	 ifstream arch("aristas.txt");
      int quantityOfNodes;
      
      if (arch.fail()) {
        cout<< "Error al abrir el archivo" <<endl;
        return 0;
      }
      
      arch >> quantityOfNodes;
      arch.close();

	int numNodes = quantityOfNodes;
	int** matrixTrans;
	bool conexo;
	vector<char> nodes;
	Grafo g(numNodes);
	g.loadMatrix();
	
	char option = ' ';
	char node1 = ' ', node2 = ' ';
	while (option != '3'){
		nodes = g.getNodes();
		
		if(g.getNodes().size() == 0){
			cout<<"El grafo ya no tiene nodo alguno"<<endl;
			break;
		}
		
		cout<<"El grafo es: \n\nNodos: ";
		for (int i=0; i<nodes.size(); i++){
			cout<<nodes[i]<<" ";
		}
		
		cout<<"\n"<<endl;
		g.printGrafo();
		cout<<endl;
		
		matrixTrans = warshall(g.getMatrixAdj(), g.getQuantityOfNodes(), conexo);
		
		if (!conexo) {
			findSourcesAndSinks(matrixTrans, g.getQuantityOfNodes(), g.getNodes());
			cout<<endl;
		}
		
		cout<<"\nOpciones a realizar: \n\n1) Eliminar nodo \n2) Encontrar ruta minima entre 2 nodos \n3) Salir"<<endl;
		cout<<"Ingresa la opcion que desees: ";
		cin>>option;
		
		if (option == '1'){
			cout<<"\nIngresa el nodo a eliminar: ";
			cin>>node1;
			
			node1 = toupper(node1);
			g.deleteNode(node1);	
		} else if (option == '2'){
			cout<<"\nIngresa el nodo de origen: ";
			cin>>node1;
			cout<<"Ingresa el nodo destino: ";
			cin>>node2;
			
			node1 = toupper(node1);
			node2 = toupper(node2);
			cout<<endl;
			findMinRoute(node1, node2, g.getQuantityOfNodes(), g.getMatrixAdj(), matrixTrans, g.getNodes());
		} else if (option == '3'){
			cout<<"Saliendo..."<<endl;
		} else {
			cout<<"\nOpcion invalida "<<endl;
		}
		
		system("pause");
		system("cls");
	}
		
	return 0;
}




