#include <unordered_map>
#include <set>

class Grouper
{
public:
	void addGroupIDs(const unsigned int *aNodeIds, const int aNodeNum)
	{
		if (aNodeNum < 2)
			return;

		int* minGroupIDPtr = nullptr;
		std::set<int*> grpIDsToChange; //group ids needs to be changed to the minGroupID

		for (int i = 0; i < aNodeNum; i++)
		{
			int nodeID = aNodeIds[i];
			auto itrFind = mapNodeGroupIDs.find(nodeID);
			int* nodeGroupIDPtr = (itrFind != mapNodeGroupIDs.end()) ? itrFind->second : nullptr;
			if (nodeGroupIDPtr)
			{
				grpIDsToChange.insert(nodeGroupIDPtr);
				//find the lowest group id
				if (minGroupIDPtr == nullptr || *minGroupIDPtr > *nodeGroupIDPtr)
				{
					minGroupIDPtr = nodeGroupIDPtr;
				}
			}
		}
		grpIDsToChange.erase(minGroupIDPtr);
		//
		if (minGroupIDPtr == nullptr)
		{
			minGroupIDPtr = new int;
			*minGroupIDPtr = 
		}
		else
		{

		}

		for (int i = 0; i < aNodeNum; i++)
		{
			int nodeID = aNodeIds[i];
			mapNodeGroupIDs[nodeID] = minGroupID;
		}
		//change all group ids in grpIDs to minGroupID
		for (int grpIDtoChange : grpIDsToChange)
		{
			for (auto &item : mapNodeGroupIDs)
			{
				if (item.second == grpIDtoChange)
					item.second = minGroupID;
			}
		}
	}
protected:
	std::unordered_map<int, int*> mapNodeGroupIDs;
};



