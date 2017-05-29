//
// Created by Qibin Chen on 29/05/2017.
//

#include "myclient.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	clientnetwork::MyClient *clientNetwork = new clientnetwork::MyClient;
	clientNetwork->SetupConnection();
//	clientNetwork->SetIP("");
	clientNetwork->LogIn("123");
	clientNetwork->UploadSinglePhoto("tmp.jpg");
	clientNetwork->ScorePhoto("2017-05-29", "tmp.jpg", 5);

	return 0;
}