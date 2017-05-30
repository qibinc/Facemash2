//
// Created by Qibin Chen on 29/05/2017.
//

#include "myclient.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	clientnetwork::MyClient *clientNetwork = new clientnetwork::MyClient;
//	clientNetwork->SetIP("");
	clientNetwork->LogIn("clientnetwork_test");
	clientNetwork->UploadSinglePhoto("star.png");
	clientNetwork->ScorePhoto("2017-05-29", "star.png", 5);

	a.exec();
	return 0;
}