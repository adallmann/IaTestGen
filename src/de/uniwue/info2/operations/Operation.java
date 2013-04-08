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

/**
 * This class implements an operation with multiple input and output-parameters.
 * 
 * @author Michael Jedich
 * 
 */
public class Operation {
	private List<GenericParameter<?>> input_;
	private List<GenericParameter<?>> output_;
	private String name_;
	private String description_;
	private boolean required_;
	private Set used_set_;
	private boolean result_negated_;
	private Class<?> mixed_type_output_;

	public Operation(String name) {
		this.name_ = name;
		this.required_ = true;
		this.result_negated_ = false;
		this.input_ = new ArrayList<GenericParameter<?>>();
		this.output_ = new ArrayList<GenericParameter<?>>();
	}

	public Operation() {
		this(null);
	}

	public void setDescription(String description) {
		this.description_ = description;
	}

	public String getDescription() {
		return description_;
	}

	public void setRequired(boolean required) {
		this.required_ = required;
	}

	public boolean isRequired() {
		return required_;
	}

	public void setName(String name) {
		this.name_ = name;
	}

	public String getName() {
		return this.name_;
	}

	public void negateResult() {
		this.result_negated_ = true;
	}

	public boolean isNegated() {
		return this.result_negated_;
	}

	public void setSetRelation(Set set) {
		this.used_set_ = set;
	}

	public Set getSetRelation() {
		return this.used_set_;
	}

	public void setMixedTypeOutput(Class<?> output) {
		this.mixed_type_output_ = output;
	}

	public boolean isMixedType() {
		return (this.mixed_type_output_ != null);
	}

	public Class<?> getMixedType() {
		return this.mixed_type_output_;
	}

	public List<GenericParameter<?>> getInputList() {
		return input_;
	}

	public void setInput(List<GenericParameter<?>> input) {
		this.input_ = input;
	}

	public List<GenericParameter<?>> getOutputList() {
		return output_;
	}

	public void setOutput(List<GenericParameter<?>> output) {
		this.output_ = output;
	}

	public void addInputParameter(GenericParameter<?> input) {
		this.input_.add(input);
	}

	public void addOutputParameter(GenericParameter<?> output) {
		this.output_.add(output);
	}
}
