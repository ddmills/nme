package nme.net;
#if (!flash)

class URLRequestMethod 
{
   public static inline var DELETE:String = "DELETE";
   public static inline var GET:String = "GET";
   public static inline var HEAD:String = "HEAD";
   public static inline var OPTIONS:String = "OPTIONS";
   public static inline var POST:String = "POST";
   public static inline var PUT:String = "PUT";
}

#else
typedef URLRequestMethod = flash.net.URLRequestMethod;
#end
