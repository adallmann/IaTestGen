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

import de.uniwue.info2.numerics.prec.DoublePrecisionFloat;
import de.uniwue.info2.numerics.prec.SinglePrecisionFloat;

/**
 * This class implements the interval-datatype.
 *
 * @author Michael Jedich
 *
 */
public class Interval<T> {
	private T upperLimit_ = null;
	private T lowerLimit_ = null;
	private Endpoints upperEndpoint_ = null;
	private Endpoints lowerEndpoint_ = null;
	private Class<?> type_;
	private boolean entire_ = false;
	private static final Class<?>[] basic_types = new Class<?>[] { Short.class, Integer.class, Long.class };

	public Interval(Class<T> type) {
		this.setType(type);
	}

	public Interval(T value) {
		this.setType(value.getClass());
		this.upperLimit_ = value;
		this.lowerLimit_ = value;
	}

	public Interval(T lower, T upper) {
		this.setType(upper.getClass());
		this.upperLimit_ = upper;
		this.lowerLimit_ = lower;
	}

	public Interval(Endpoints lower, T upper) {
		this.setType(upper.getClass());
		this.lowerEndpoint_ = lower;
		this.upperLimit_ = upper;
	}

	public Interval(T lower, Endpoints upper) {
		this.setType(lower.getClass());
		this.upperEndpoint_ = upper;
		this.lowerLimit_ = lower;
	}

	public Interval(Endpoints lower, Endpoints upper, Class<T> type) {
		this.setType(type);
		this.lowerEndpoint_ = lower;
		this.upperEndpoint_ = upper;
	}

	public T getLower_limit() {
		return lowerLimit_;
	}

	public T getUpper_limit() {
		return upperLimit_;
	}

	public Endpoints getUpperEndpoint() {
		return upperEndpoint_;
	}

	public Endpoints getLowerEndpoint() {
		return lowerEndpoint_;
	}

	public void setEndpoint(Endpoints upperEndpoint, Endpoints lowerEndpoint) {
		setUpperEndpoint(upperEndpoint);
		setLowerEndpoint(lowerEndpoint);
	}

	public void setUpperEndpoint(Endpoints upperCardinality) {
		this.upperEndpoint_ = upperCardinality;
		this.upperLimit_ = null;
	}

	public void setLowerEndpoint(Endpoints lowerCardinality) {
		this.lowerEndpoint_ = lowerCardinality;
		this.lowerLimit_ = null;
	}

	public void emptyInterval() {
		this.upperLimit_ = null;
		this.lowerLimit_ = null;
		this.upperEndpoint_ = null;
		this.lowerEndpoint_ = null;
	}

	public void setEntireInterval() {
		this.upperLimit_ = null;
		this.lowerLimit_ = null;
		this.upperEndpoint_ = null;
		this.lowerEndpoint_ = null;
		this.entire_ = true;
	}

	public void setLimits(T lower_limit, T upper_limit) {
		setUpper_limit(upper_limit);
		setLower_limit(lower_limit);
	}

	public void setUpper_limit(T upper_limit) {
		if (!this.getTypeClass().isInstance(upper_limit)) {
			throw new IllegalArgumentException("incompatible type: " + upper_limit.getClass());
		}

		this.upperLimit_ = upper_limit;
		this.upperEndpoint_ = null;
	}

	public void setLower_limit(T lower_limit) {
		if (!this.getTypeClass().isInstance(lower_limit)) {
			throw new IllegalArgumentException("incompatible type: " + lower_limit.getClass());
		}

		this.lowerLimit_ = lower_limit;
		this.lowerEndpoint_ = null;
	}

	public void specifySubclass(Class<? extends T> subClass) {
		this.setType(subClass);
	}

	public boolean hasType(Class<?> type) {
		return type.isAssignableFrom(this.getTypeClass());
	}

	public Class<?> getTypeClass() {
		return this.type_;
	}

	public boolean isEmpty() {
		if (this.lowerLimit_ != null && this.upperLimit_ != null) {
			return false;
		}
		if (this.lowerEndpoint_ != null && this.upperEndpoint_ != null) {
			return false;
		}
		if (this.lowerLimit_ != null && this.upperEndpoint_ != null) {
			return false;
		}
		if (this.lowerEndpoint_ != null && this.upperLimit_ != null) {
			return false;
		}
		if (this.entire_) {
			return false;
		}
		return true;
	}

	public boolean isEntire() {
		return this.entire_; 
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
			throw new IllegalArgumentException("incompatible type, accepted types:\n" + accepted_types + "\n");
		} else {
			this.type_ = cl;
		}
	}

	public static List<Class<?>> getAcceptedTypes() {
		List<Class<?>> accepted_types = new ArrayList<Class<?>>();
		for (Class<?> cl : basic_types) {
			accepted_types.add(cl);
		}

		// TODO:
		// add float types
		// same package as FloatingPoint.class
		accepted_types.add(SinglePrecisionFloat.class);
		accepted_types.add(DoublePrecisionFloat.class);

		return accepted_types;
	}

}
