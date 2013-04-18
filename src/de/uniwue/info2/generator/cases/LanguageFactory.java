/*
 *    IaTestGen - Interval arithmetic test generator
 *    Copyright 2013
 *
 *    Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
 *    Institute of Computer Science,
 *    University of Wuerzburg, Germany
 *
 *    Michael Jedich (m.jedich@gmail.com)
 *    University of Wuerzburg, Germany
 *
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
package de.uniwue.info2.generator.cases;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import de.uniwue.info2.generator.cases.cpp.CppBoostUnitTestLibrary;
import de.uniwue.info2.generator.cases.cpp.CppSpecification;
import de.uniwue.info2.generator.cases.cpp.CppUniWueP1788IEEE754ArithmeticLibrary;
import de.uniwue.info2.generator.cases.cpp.CppUniWueP1788MPFLArithmeticLibrary;

/**
 * This class is used to instantiate LanguageSpecification, ArithmeticLibrarySpecification and UnitTestLibrarySpecification.
 *
 * @author Michael Jedich
 *
 */
public class LanguageFactory {
	private HashMap<String, LanguageSpecification> languageMap_;
	private HashMap<String, UnitTestLibrarySpecification> unitTestLibrariesMap_;
	private HashMap<String, ArithmeticLibrarySpecification> arithmeticLibrariesMap_;

	private List<LanguageSpecification> availableLanguageSpecifications_;
	private HashMap<String, List<UnitTestLibrarySpecification>> availableUnitTestLibraries_;
	private HashMap<String, List<ArithmeticLibrarySpecification>> availableArithmeticLibraries_;

	public List<LanguageSpecification> getAvailableLanguageSpecifications_() {
		if (availableLanguageSpecifications_.isEmpty()) {
			throw new IllegalArgumentException("No language specification defined!");
		}
		return availableLanguageSpecifications_;
	}

	public List<UnitTestLibrarySpecification> getAvailableUnitTestLibraries_(String language) {
		if (availableUnitTestLibraries_.get(language) == null) {
			throw new IllegalArgumentException("No interval arithmetic library defined for: " + language);
		}

		return availableUnitTestLibraries_.get(language);
	}

	public List<ArithmeticLibrarySpecification> getAvailableArithmeticLibraries_(String language) {
		if (availableArithmeticLibraries_.get(language) == null) {
			throw new IllegalArgumentException("No unit-test library defined for: " + language);
		}
		return availableArithmeticLibraries_.get(language);
	}

	// TODO:
	// create plugin structur with java reflection
	// save plugin-folder location in LanguageSpecification-object
	private List<Class<? extends LanguageSpecification>> listLanguageSpecificationPlugins(File plugin_folder) {
		List<Class<? extends LanguageSpecification>> specs = new ArrayList<Class<? extends LanguageSpecification>>();
		specs.add(CppSpecification.class);
		return specs;
	}

	// TODO:
	private List<Class<? extends UnitTestLibrarySpecification>> listUnitTestLibrarySpecificationPlugins(File language_folder) {
		List<Class<? extends UnitTestLibrarySpecification>> specs = new ArrayList<Class<? extends UnitTestLibrarySpecification>>();
		specs.add(CppBoostUnitTestLibrary.class);
		return specs;
	}

	// TODO:
	private List<Class<? extends ArithmeticLibrarySpecification>> listArithmeticLibrarySpecificationPlugins(File language_folder) {
		List<Class<? extends ArithmeticLibrarySpecification>> specs = new ArrayList<Class<? extends ArithmeticLibrarySpecification>>();
		specs.add(CppUniWueP1788IEEE754ArithmeticLibrary.class);
		specs.add(CppUniWueP1788MPFLArithmeticLibrary.class);
		return specs;
	}

	public LanguageFactory() {
		languageMap_ = new HashMap<String, LanguageSpecification>();
		unitTestLibrariesMap_ = new HashMap<String, UnitTestLibrarySpecification>();
		arithmeticLibrariesMap_ = new HashMap<String, ArithmeticLibrarySpecification>();

		availableLanguageSpecifications_ = new ArrayList<LanguageSpecification>();
		availableUnitTestLibraries_ = new HashMap<String, List<UnitTestLibrarySpecification>>();
		availableArithmeticLibraries_ = new HashMap<String, List<ArithmeticLibrarySpecification>>();

		// TODO:
		List<Class<? extends LanguageSpecification>> lClasses = listLanguageSpecificationPlugins(null);

		for (Class<? extends LanguageSpecification> lClass : lClasses) {
			try {
				LanguageSpecification lSpec = lClass.newInstance();

				String lKey = lSpec.getOptionName();
				if (lKey.contains("_")) {
					throw new IllegalAccessException("option-name of your language specification contains \"_\"-character");
				}

				languageMap_.put(lKey, lSpec);
				availableLanguageSpecifications_.add(lSpec);

				// TODO: use folder of current language specification
				List<Class<? extends UnitTestLibrarySpecification>> uClasses = listUnitTestLibrarySpecificationPlugins(null); 

				for (Class<? extends UnitTestLibrarySpecification> uClass : uClasses) {
					UnitTestLibrarySpecification uSpec = uClass.newInstance();
					if (uSpec.getOptionName().contains("_")) {
						throw new IllegalAccessException("option-name of your unit-test specification contains \"_\"-character");
					}

					unitTestLibrariesMap_.put(uSpec.getOptionName(), uSpec);
					if (availableUnitTestLibraries_.containsKey(lKey)) {
						List<UnitTestLibrarySpecification> uList = availableUnitTestLibraries_.get(lKey);
						uList.add(uSpec);
					} else {
						List<UnitTestLibrarySpecification> uList = new ArrayList<UnitTestLibrarySpecification>();
						uList.add(uSpec);
						availableUnitTestLibraries_.put(lKey, uList);
					}
				}

				// TODO:
				List<Class<? extends ArithmeticLibrarySpecification>> aClasses = listArithmeticLibrarySpecificationPlugins(null); 

				for (Class<? extends ArithmeticLibrarySpecification> aClass : aClasses) {
					ArithmeticLibrarySpecification aSpec = aClass.newInstance();
					if (aSpec.getOptionName().contains("_")) {
						throw new IllegalAccessException("option-name of your ia specification contains \"_\"-character");
					}
					arithmeticLibrariesMap_.put(aSpec.getOptionName(), aSpec);
					if (availableArithmeticLibraries_.containsKey(lKey)) {
						List<ArithmeticLibrarySpecification> aList = availableArithmeticLibraries_.get(lKey);
						aList.add(aSpec);
					} else {
						List<ArithmeticLibrarySpecification> aList = new ArrayList<ArithmeticLibrarySpecification>();
						aList.add(aSpec);
						availableArithmeticLibraries_.put(lKey, aList);
					}
				}

			} catch (InstantiationException e) {
				e.printStackTrace();
			} catch (IllegalAccessException e) {
				e.printStackTrace();
			} catch (SecurityException e) {
				e.printStackTrace();
			} catch (IllegalArgumentException e) {
				e.printStackTrace();
			}
		}
	}

	public LanguageSpecification getLanguageSpecification(String specification) {
		String[] parameter = specification.split("_");
		if (parameter.length == 1) {
			return getAllCombinations(parameter[0]);
		} else if (parameter.length == 3) {
			return getCustomLanguageSpecification(parameter[0], parameter[1], parameter[2]);
		}
		return null;
	}

	private LanguageSpecification getAllCombinations(String languageSpecification) {
		LanguageSpecification customSpec = languageMap_.get(languageSpecification);
		for (ArithmeticLibrarySpecification lib : getAvailableArithmeticLibraries_(languageSpecification)) {
			customSpec.addArithmeticLibrary(lib);
		}
		for (UnitTestLibrarySpecification lib : getAvailableUnitTestLibraries_(languageSpecification)) {
			customSpec.addUnitTestLibrary(lib);
		}
		return customSpec;
	}

	private LanguageSpecification getCustomLanguageSpecification(String languageSpecification, String unitTestLibrarySpecification,
			String arithmeticLibrarySpecification) {
		LanguageSpecification customSpec = languageMap_.get(languageSpecification);
		customSpec.addArithmeticLibrary(arithmeticLibrariesMap_.get(arithmeticLibrarySpecification));
		customSpec.addUnitTestLibrary(unitTestLibrariesMap_.get(unitTestLibrarySpecification));
		return customSpec;
	}

}
