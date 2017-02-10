'use strict';

const removeDuplicateLettersEnd = function (string) {
	var resStr = "";

	strStep:
		for (var i = 0; i < string.length; i++) {
			var char = string[i];
			for (var j = i + 1; j < string.length; j++)
				if (string[j] == char) continue strStep;
			resStr += char;
		}

	return resStr;
};