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
	LoopHeader:
		br label %Loop
	
	Loop:
		%index = phi i64 [0, %LoopHeader], [%nextindex, %LoopTail]
		%nextindex = add i64 %index, 1
		
		%temp1 = ptrtoint i8* %str1 to i64
		%temp2 = add i64 %temp1, %index
		%newptr1 = inttoptr i64 %temp2 to i8*
		%charval1 = load i8, i8* %newptr1
		
		%temp3 = ptrtoint i8* %str2 to i64
		%temp4 = add i64 %temp3, %index
		%newptr2 = inttoptr i64 %temp4 to i8*
		%charval2 = load i8, i8* %newptr2
		
		%cond1 = icmp eq i8 %charval1, 0
		%cond2 = icmp eq i8 %charval2, 0
		%cond3 = and i1 %cond1, %cond2
		br i1 %cond3, label %End, label %LoopTail 		
	
	LoopTail:
		%cond = icmp eq i8 %charval1, %charval2
		br i1 %cond, label %Loop, label %End
	
	End:
		%charval1ext = zext i8 %charval1 to i32
		%charval2ext = zext i8 %charval2 to i32
		%result = sub i32 %charval1ext, %charval2ext
		ret i32 %result
}

define i8* @string_chr(i8* %str, i8 %c) {
	LoopHeader:
		br label %Loop
	
	Loop:
		%index = phi i64 [0, %LoopHeader], [%nextindex, %Loop]
		%nextindex = add i64 %index, 1
		%temp1 = ptrtoint i8* %str to i64
		%temp2 = add i64 %temp1, %index
		%newptr = inttoptr i64 %temp2 to i8*
		%charval = load i8, i8* %newptr
		%cond = icmp eq i8 %charval, %c
		br i1 %cond, label %End, label %Loop
	
	End:
		ret i8* %newptr
}

define i8* @string_cpy(i8* %dest, i8* %src) {
	LoopHeader:
		br label %Loop
	
	Loop:
		%index = phi i64 [0, %LoopHeader], [%nextindex, %Loop]
		%nextindex = add i64 %index, 1
		
		%temp1 = ptrtoint i8* %src to i64
		%temp2 = add i64 %temp1, %index
		%newptr1 = inttoptr i64 %temp2 to i8*
		%charval = load i8, i8* %newptr1
		
		%temp3 = ptrtoint i8* %dest to i64
		%temp4 = add i64 %temp3, %index
		%newptr2 = inttoptr i64 %temp4 to i8*
		store i8 %charval, i8* %newptr2
		
		%cond = icmp eq i8 %charval, 0
		br i1 %cond, label %End, label %Loop
	
	End:
		ret i8* %dest
}

define i8* @string_cat(i8* %dest, i8* %src) {
	ret i8* %dest
}