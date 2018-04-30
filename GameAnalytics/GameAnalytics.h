#pragma once
#include <string>

#include "dllimport.h"

using namespace std;

#define GA GameAnalytics::getInstance()

//port to connect to
const int COMMUNICATION_PORT = 5000;
const int COMMUNICATION_SIZE = 256;

//forward declaration
namespace sf
{
	class TcpSocket;
} // namespace sf

//used to deduct variable types during updates
enum class EDataType
{
	INT,
	FLOAT,
	STRING,
	HEATMAP,
};

enum class EUpdate
{
	OVERWRITE,
	OFFSET,
};

//data type used to update a heat-map
struct HeatMapUpdate
{
	int x;
	int y;
	int** v;
};

/*
* class GameAnalytics
*
* singleton that initialises various components required
* to communicate with the game analytics server, and track
* required data
*
* @author: Bradley Booth, Academy of Interactive Entertainment, 2018
*/
class GameAnalytics
{
private:

	/*
	* GameAnalytics()
	* default constructor
	*/
	DLL_EXP GameAnalytics();

	/*
	* ~GameAnalytics()
	* default destructor
	*/
	DLL_EXP ~GameAnalytics();

public:

	sf::TcpSocket* client = nullptr;

	/*
	* getInstance
	*
	* gets a pointer to the only instance of the game analytics object,
	* creates the object if it doesn't already exist
	*
	* @returns static GameAnalytics* - pointer to the singleton
	*/
	DLL_EXP static GameAnalytics* getInstance();

	/*
	* connect
	*
	* attempts to connect the client socket to the server
	*
	* @returns bool - result of the attempted connection
	*/
	DLL_EXP bool connect();

	/*
	* updateData
	*
	* attempts to send a data update to the server
	*
	* @param string name - name of the data to update
	* @param void* data - pointer to the data to send
	* @param EDataType dataType - the type of data that is being sent
	* @param EUpdateType updateType - the type of update that is being sent
	* @returns void
	*/
	DLL_EXP void updateData(string name, void* data, EDataType dataType, EUpdate updateType);
};