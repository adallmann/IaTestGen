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
package de.uniwue.info2.generator;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;

import de.uniwue.info2.operations.Operation;

/**
 * This class is used to collect operations, sort them by name and generate lists for each
 * name.
 * 
 * @author Michael Jedich
 * 
 */
public class OperationsPool {

	private HashMap<String, ArrayList<Operation>> operationsByName_;
	private ArrayList<Operation> operationsAll_;

	/**
	 * Constructor.
	 */
	public OperationsPool() {
		this.operationsByName_ = new HashMap<String, ArrayList<Operation>>();
		this.operationsAll_ = new ArrayList<Operation>();
	}

	/**
	 * Add one operation.
	 * 
	 * @param name
	 *            name of operation
	 * @param op
	 *            operation-object
	 */
	public void addOperation(String name, Operation op) {
		if (name == null) {
			throw new NullPointerException("given operation name is null");
		}
		if (op == null) {
			throw new NullPointerException("given operation is null");
		}
		op.setName(name);
		operationsAll_.add(op);

		if (operationsByName_.containsKey(name)) {
			operationsByName_.get(name).add(op);
		} else {
			ArrayList<Operation> operations = new ArrayList<Operation>();
			operations.add(op);
			operationsByName_.put(name, operations);
		}
	}

	/**
	 * Get all operations as an iterator.
	 * 
	 * @return iterator
	 */
	public Iterator<Operation> getOperations() {
		return operationsAll_.iterator();
	}

	/**
	 * Get operations for specific name.
	 * 
	 * @param name
	 *            name of operation
	 * @return iterator
	 */
	public Iterator<Operation> getOperationsByName(String name) {
		if (name == null) {
			throw new NullPointerException("given operation name is null");
		}
		return operationsByName_.get(name).iterator();
	}

}
