define i32 @string_len(i8* %str) {
	%size = add i32 1, 0
	ret i32 %size
}

define i32 @string_cmp(i8* %str1, i8* %str2) {
	%size = add i32 1, 0
	ret i32 %size
}

define i8* @string_chr(i8* %str) {
	%size = inttoptr i8 1 to i8*
	ret i8* %size
}

define i8* @string_cpy(i8* %str) {
	%size = inttoptr i8 1 to i8*
	ret i8* %size
}