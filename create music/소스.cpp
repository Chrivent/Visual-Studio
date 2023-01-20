#include<iostream>
#include<fstream>

#include<Windows.h>
#include "RtMidi.h"

#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")

class CreateMusic
{
private:
	std::ofstream* file;

	int startHeight;

	const std::string fileName = "run";
	const std::string filePath = "C:\\Users\\Yechan Ha\\AppData\\Roaming\\.minecraft\\saves\\새로운 세계 (1)\\datapacks\\build_create_mod_music\\data\\build\\functions";

	const int sheet[37] = { 0,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1,1,0,1,0,1,1,0 };
	const std::string chord[4] = { "coal", "iron_ingot", "gold_ingot", "diamond" };
	const std::string syllable[12] =
	{
		"red_wool",
		"red_bed",
		"orange_wool",
		"orange_bed",
		"yellow_wool",
		"lime_wool",
		"lime_bed",
		"light_blue_wool",
		"light_blue_bed",
		"blue_wool",
		"blue_bed",
		"purple_wool"
	};

public:
	CreateMusic(std::string fileName, int startHeight) : startHeight(startHeight)
	{
		file = new std::ofstream(filePath + "\\" + fileName + ".mcfunction");
	}

	void BuildOneSheet(int x)
	{
		for (int i = 0; i < sizeof(sheet) / sizeof(int); i++)
		{
			std::string color;

			if (sheet[i] == 0)
				color = "black";
			else
				color = "white";

			*file << "setblock ~" << x << " ~" << i + startHeight << " ~-1 minecraft:" + color + "_wool" << std::endl;

			std::string tmpChord;

			if (i < 6)
				tmpChord = chord[0];
			else if (i < 18)
				tmpChord = chord[1];
			else if (i < 30)
				tmpChord = chord[2];
			else
				tmpChord = chord[3];

			std::string tmpSyllable = syllable[(i + 6) % 12];

			*file << "setblock ~" << x << " ~" << i + startHeight << " ~-2 create:redstone_link[facing = north, powered = false, receiver = false]{FrequencyFirst: {Count:1b,id : \"minecraft:" + tmpChord + "\"},FrequencyLast : {Count:1b,id : \"minecraft:" + tmpSyllable + "\"}}" << std::endl;
		}
	}

	void BuildSyllableTest()
	{
		for (int i = 0; i < sizeof(sheet) / sizeof(int); i++)
		{
			BuildOneSheet(i);

			*file << "setblock ~" << i << " ~" << i + startHeight << " ~-1 create:redstone_contact[facing = south, powered = false]" << std::endl;
		}
	}

	~CreateMusic()
	{
		file->close();

		delete file;
	}
};

int main()
{
	//CreateMusic createMusic("run", 4);

	//createMusic.BuildSyllableTest();

	RtMidiOut* midiout = new RtMidiOut();
	std::vector<unsigned char> message;
	// Check available ports.
	unsigned int nPorts = midiout->getPortCount();
	if (nPorts == 0) {
		std::cout << "No ports available!\n";
		goto cleanup;
	}

	for (unsigned int i = 0; i < nPorts; i++) {
		std::cout << midiout->getPortName(i) << std::endl;
	}

	// Open first available port.
	midiout->openPort(0);

	// Send out a series of MIDI messages.

	// Program change: 192, 5
	message.push_back(192);
	message.push_back(5);
	midiout->sendMessage(&message);

	// Control Change: 176, 7, 100 (volume)
	message[0] = 176;
	message[1] = 7;
	message.push_back(100);
	midiout->sendMessage(&message);

	// Note On: 144, 60, 90
	message[0] = 0x90;
	message[1] = 60;
	message[2] = 90;
	midiout->sendMessage(&message);
	Sleep(500);

	// Note Off: 128, 60, 40
	message[0] = 0x80;
	message[1] = 60;
	message[2] = 40;
	midiout->sendMessage(&message);

	// Note On: 144, 62, 90
	message[0] = 0x90;
	message[1] = 62;
	message[2] = 90;
	midiout->sendMessage(&message);
	Sleep(500);

	// Note Off: 128, 62, 40
	message[0] = 0x80;
	message[1] = 62;
	message[2] = 40;
	midiout->sendMessage(&message);

	// Note On: 144, 64, 90
	message[0] = 0x90;
	message[1] = 64;
	message[2] = 90;
	midiout->sendMessage(&message);
	Sleep(500);

	// Note Off: 128, 64, 40
	message[0] = 0x80;
	message[1] = 64;
	message[2] = 40;
	midiout->sendMessage(&message);


	// Clean up
cleanup:
	delete midiout;

	return 0;
}