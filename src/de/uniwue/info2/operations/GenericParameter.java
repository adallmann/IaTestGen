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
package de.uniwue.info2.operations;

import java.util.ArrayList;
import java.util.List;

import de.uniwue.info2.miscellaneous.ClassDiscovery;
import de.uniwue.info2.numerics.FloatingPoint;

/**
 * This generic class is used to store different parameter of an operation.
 * 
 * @author Michael Jedich
 * 
 */
public class GenericParameter<T> {
	private T value;
	private Class<?> type_;

	private static final Class<?>[] basic_types = new Class<?>[] { Short.class, Integer.class,
			Long.class, Boolean.class, Interval.class, Endpoints.class };

	public GenericParameter(T initValue) {
		this.setType(initValue.getClass());
		this.setValue(initValue);
	}

	public boolean hasType(Class<?> type) {
		return type.isAssignableFrom(this.getTypeClass());
	}

	public Class<?> getTypeClass() {
		return this.type_;
	}

	public void setValue(T newValue) {
		if (!this.getTypeClass().isInstance(newValue)) {
			throw new IllegalArgumentException("incompatible type: " + newValue.getClass());
		}
		value = newValue;
	}

	public T getValue() {
		return value;
	}

	private void setType(Class<?> cl) {
		List<Class<?>> accepted_types = getAcceptedTypes();

		for (Class<?> c : accepted_types) {
			if (c.getSuperclass() == cl) {
				accepted_types.add(cl);
				break;
			}
		}

		if (!accepted_types.contains(cl)) {
			throw new IllegalArgumentException("incompatible type, accepted types:\n"
					+ accepted_types + "\n");
		} else {
			this.type_ = cl;
		}
	}

	public static List<Class<?>> getAcceptedTypes() {
		List<Class<?>> accepted_types = new ArrayList<Class<?>>();
		for (Class<?> cl : basic_types) {
			accepted_types.add(cl);
		}
		// add float types
		for (Class<? extends FloatingPoint> cl : ClassDiscovery
				.findInSubpackages(FloatingPoint.class)) {
			accepted_types.add(cl);
		}
		return accepted_types;
	}
}
