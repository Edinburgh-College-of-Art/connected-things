//====================================================================
char *append_str(char *here, char *s)
{
  while (*here++ = *s++) {}
  return here - 1;
}

char *append_ul(char *here, unsigned long u)
{
  char buf[20];
  return append_str(here, ultoa(u, buf, 10));
}

//====================================================================

// This is called once per iteration to read the pin
// and send a POST to trigger the IFTTT/Maker event

void update_event(const char* data)
{
  client.connect("maker.ifttt.com", 80);  // connect to the Maker event server

  char post_rqst[1000];    // hand-calculated to be big enough
  char *p = post_rqst;
  makeIftttPostHeader(p);

  char *content_length_here = p; // we need to remember where the content length will go, which is
  p = append_str(p, "NN\r\n");   // it's always two digits, so reserve space for them (the NN)
  p = append_str(p, "\r\n");     // end of headers
  char *json_start = p;          // construct the JSON; remember where we started so we will know len

  p = append_str(p, "{\"value1\":\"");
  p = append_str(p, data);
  p = append_str(p, "\",\"value2\":\"");
  p = append_ul(p, millis() / 1000);
  p = append_str(p, "\",\"value3\":\"");
  p = append_str(p, "via #IFTTT");
  p = append_str(p, "\"}");

  // go back and fill in the JSON length
  // we just know this is at most 2 digits (and need to fill in both)
  int i = strlen(json_start);
  content_length_here[0] = '0' + (i / 10);
  content_length_here[1] = '0' + (i % 10);
  
  client.print(post_rqst);   // finally we are ready to send the POST to the server!
  client.stop();
}

void makeIftttPostHeader(char *p)
{
  p = append_str(p, "POST /trigger/");
  p = append_str(p, MakerIFTTT_Event);
  p = append_str(p, "/with/key/");
  p = append_str(p, MakerIFTTT_Key);
  p = append_str(p, " HTTP/1.1\r\n");
  p = append_str(p, "Host: maker.ifttt.com\r\n");
  p = append_str(p, "Content-Type: application/json\r\n");
  p = append_str(p, "Content-Length: ");
}
//====================================================================
