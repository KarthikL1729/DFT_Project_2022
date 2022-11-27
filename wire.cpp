#include <bits/stdc++.h>
using namespace std;

struct wire{
		int name;						// 50 and above
		int input;
		vector<int> outputs;
		char state = 'x';				// 0, 1, D, E, X
		int fault = 2;				// NA = 2, SA0 = 0, SA1 = 1
};


struct gate{
		int name;						// 0 - 49
		int ip1;
		int ip2;
		int type;		// AND, OR, NAND, NOR, NOT
		int op;

};

void faultActivate(wire* faultSite, int faultType){
	faultSite->fault = faultType;
	switch(faultType){
		case 0:
			faultSite->state = 'D';
			faultSite->fault = 0;
			break;
		case 1:
			faultSite->state = 'E';
			faultSite->fault = 1;
			break;
	}
	int gateID = faultSite->input;
	if(gateID<50){
		gate gateToActivate = findGate(gateList, gateID);

		wire ip1wire = findWire(wireList, gateToActivate.ip1);
		wire ip2wire = findWire(wireList, gateToActivate.ip2);

		switch(gateToActivate.type){
			case 0:
				if(faultType == 0){
					ip1wire->state = '1';
					ip2wire->state = '1';
				}
				else{
					ip1wire->state = '0'
				}
				break;
			case 1:
				if(faultType == 0){
					ip1wire->state = '1';
				}
				else{
					ip1wire->state = '0';
					ip2wire->state = '0';
				}
				break;	
			case 2:
				if(faultType == 0){
					ip1wire->state = '0'
				}
				else{
					ip1wire->state = '1';
					ip2wire->state = '1';
				}
				break;
			case 3:
				if(faultType == 0){
					ip1wire->state = '0';
					ip2wire->state = '0';
				}
				else{
					ip1wire->state = '1';
				}
				break;
		}
	}
	else if(gateID>= 50){
		ipWire = findWire(wireList, gateID);
		if(faultType == 0){
			ipWire->state = '1';
		}
		else if(faultType == 1){
			ipWire->state = '0';
		}
	}

}
