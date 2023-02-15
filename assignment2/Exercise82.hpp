#ifndef SUBMISSION_EXERCISE82_HPP_
#define SUBMISSION_EXERCISE82_HPP_

template<typename T>
T CalcAbs(T val) {

	T result = val;

	if (val < 0){
		result = - val;
	}

	return result;
}


#endif /* SUBMISSION_EXERCISE82_HPP_ */
