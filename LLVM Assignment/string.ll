define i32 @string_len(i8* %str) {
	LoopHeader:
		br label %Loop
	Loop:
		%size = phi i64 [0, %LoopHeader], [%nextsize, %Loop]
		%nextsize = add i64 %size, 1
		%temp1 = ptrtoint i8* %str to i64
		%temp2 = add i64 %temp1, %size
		%newptr = inttoptr i64 %temp2 to i8*
		%charval = load i8, i8* %newptr
		%cond = icmp eq i8 %charval, 0
		br i1 %cond, label %End, label %Loop
	End:
		%result = trunc i64 %size to i32
		ret i32 %result
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