/* ===================================== 
 *	dbinitialiser.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#ifndef STORE_INITIALISER_H_
#define STORE_INITIALISER_H_

#include <QString>

class StoreInitialiser
{
public:
	StoreInitialiser() = default;
	
	void createStore(const QString &base);
	void createDataTables();
};

#endif /* DBINITIALISER_H_ */
