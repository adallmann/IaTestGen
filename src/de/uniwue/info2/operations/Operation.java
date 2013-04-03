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

	public String getDescription() {
		return description_;
	}

	public void setDescription(String description) {
		this.description_ = description;
	}

	public boolean isRequired() {
		return required_;
	}

	public void setRequired(boolean required) {
		this.required_ = required;
	}

	public Operation() {
		this(null);
	}

	public Operation(String name) {
		this.name_ = name;
		this.required_ = true;
		this.input_ = new ArrayList<GenericParameter<?>>();
		this.output_ = new ArrayList<GenericParameter<?>>();
	}

	public void setName(String name) {
		this.name_ = name;
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

	public String getName() {
		return name_;
	}

	public void addInputParameter(GenericParameter<?> input) {
		this.input_.add(input);
	}

	public void addOutputParameter(GenericParameter<?> output) {
		this.output_.add(output);
	}
}
