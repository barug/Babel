#include <QDebug>
#include <iostream>
#include "BabelClient.h"

#include        <QTcpSocket>
#include	<QNetworkInterface>

#include <iostream>

int             main(int ac, char *av[])
{
  BabelClient	client(ac, av);
  client.start();
}
