#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "IOCompletionPort.h"

using namespace std;

int main()
{
	IOCompletionPort icp;
	icp.InitSocket();

	const UINT16 maxClientCount = 50;
	const UINT16 serverPort = 12034;

	icp.BindandListen(serverPort);
	icp.StartServer(maxClientCount);
	getchar();
	icp.DestroyThread();

	return 0;
}

