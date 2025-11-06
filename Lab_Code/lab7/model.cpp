/*
 *  model.cpp  -  supplied model table  (10 models)
 *  GenAI Token Top-Up Station  (Fall 2025)
 *  Hongmei WANG: hwangfy@connect.ust.hk
 */

#include "utils.h"

/* Model Table is a dynamic array indexed by the model ID.  */
static Model models[MAX_MODEL] = {
    {1,  "GPT-3.5-Turbo",     1},
    {2,  "GPT-4",             2},
    {3,  "GPT-4-Turbo",       3},
    {4,  "Gemini-Pro",        1},
    {5,  "Gemini-Ultra",      4},
    {6,  "Claude-3-Haiku",    1},
    {7,  "Claude-3-Sonnet",   2},
    {8,  "Claude-3-Opus",     5},
    {9,  "Llama-3-70B",       1},
    {10, "Mistral-Large",     3}
};

/* File-scoped static variables: total model count */
static int modelCnt = 10;

/* Accessor functions */
Model* getModelTable() { return models; }
int    getModelCount() { return modelCnt; }


/* Get token price for a specific model ID */
int getModelPrice(int modelId) {
    for (int i = 0; i < modelCnt; ++i) {
        if (models[i].modelId == modelId) {
            return models[i].pricePerToken; 
        }
    }
    return 0; /* Model not found */
}
