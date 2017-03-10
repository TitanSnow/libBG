var fs=require("fs")
var fn=process.argv[2]
var str=fs.readFileSync(fn).toString()
;(function rp(str){
	str=str.replace(/\r\n|\r|\n/g,"\n")
	var arr=str.split("\n")
	var reg=/^#\s*include\s*"(.*)"\s*$/
	var pms=[]
	arr.forEach(function(ln,i){
		var rst=reg.exec(ln)
		if(rst===null) return
		pms.push(new Promise(function(suc,fal){
			fs.readFile(rst[1],function(err,str){
				if(err)
					fal(err)
				else{
					str=str.toString()
					rp(str).then(function(str){
						arr[i]=str
						suc()
					}).catch(fal)
				}
			})
		}))
	})
	if(pms.length)return new Promise(function(suc,fal){
		Promise.all(pms).then(function(){suc(arr.join("\n"))}).catch(fal)
	})
	return new Promise(function(suc){suc(arr.join("\n"))})
})(str).then(function(str){process.stdout.write(str,"utf8")})
