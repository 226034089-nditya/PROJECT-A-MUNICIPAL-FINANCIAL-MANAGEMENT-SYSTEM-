/* assets.h - Asset Management module */

#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS 100
#define NUMBER_OF_TYPES 5

void assetMenu(void);
void addAsset(void);
void displayAssets(void);
void searchAsset(void);
void displayOneAsset(int index);

int findAssetById(char id[]);

/* used by the reports module */
int getAssetCount(void);
double getAssetValue(int index);
int getAssetTypeNumber(int index);
void getAssetTypeName(int typeNumber, char name[]);

#endif
