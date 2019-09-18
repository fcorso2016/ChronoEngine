// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "FormulaModule.h"
#include "Templates/SubclassOf.h"

UFormulaModule* UFormulaModule::ConstructFormulaModule(UObject* Outer, TSubclassOf<UFormulaModule> ModuleClass) {
	return NewObject<UFormulaModule>(Outer, ModuleClass);
}
