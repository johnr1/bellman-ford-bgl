#include "../include/graph.h"

/**
 * Translates the GraphType enum to
 * std::string;
 * 
 * @gt The GraphType class enum
 * @return The string corrisponding to that graph type
 * 
 */
std::string graphName(GraphType gt){
	switch(gt) {
        case GraphType::random : return "Random";
        case GraphType::grid : return "Grid";
    }
	return "ERR";
}

std::string labelName(int label){
	switch(label) {
        case NEG_CYCLE : return "V-";
		case ATT_TO_CYCLE : return "V-";
		case FINITE : return "Vf";
        case PLUS : return "V+";
    }
	return "ERR";
}

