#include "util.h"

coordinates getCoord(float X, float Y, float Z){
  coordinates c;
  c.X = X;
  c.Y = Y;
  c.Z= Z;
  c.W = 1;//coordenada homogênea
  return c;
}

coordinates SRUToSRD(coordinates SRU,coordinates min, coordinates max, Environment e){
  coordinates nc; //coordenadas normalizadas
  coordinates dc; //coordenadas do dispositivo

  //A transformação de coordenadas do usuário (x,y) para coordenadas normalizadas, denominada transformação de visualização
  nc.X = (SRU.X-min.X)/(max.X-min.X);
  nc.Y = (SRU.Y-min.Y)/(max.Y-min.Y);

  //O mapeamento de coordenadas normalizadas (reais) para coordenadas do dispositivo gráfico de saída (inteiras) é uma transformação linear e pode ser considerada como
  dc.X=round(nc.X*(e.width-1));
  dc.Y=round(nc.Y*(e.height-1));
  
  return dc;
}

rgb_color getRGB(int R,int G,int B){
  rgb_color c;
  c.red=R;
  c.green=G;
  c.blue=B;
  return c;
}

hsv_color getHSV(int H, int S, int V){
	hsv_color hsv;
	hsv.hue=H;        
    hsv.sat=((double)S/100); //pra ficar entre 0 e 1        
    hsv.val=((double)V/100);
    return hsv;
}

rgb_color HSVToRGB(hsv_color hsv)
{
	double H=hsv.hue;
	double S=hsv.sat;
	double V=hsv.val;
	while (H < 0) { H += 360; };
	while (H >= 360) { H -= 360; };
	double R, G, B;
	if (V <= 0)
	{ 
		R = G = B = 0;
	}
	else if (S <= 0)
	{
		R = G = B = V;
	}
	else
	{
		double hf = H / 60.0;
		int i = (int)floor(hf);
		double f = hf - i;
		double pv = V * (1 - S);
		double qv = V * (1 - S * f);
		double tv = V * (1 - S * (1 - f));
		switch (i)
		{
			case 0:
			R = V;
			G = tv;
			B = pv;
			break;
		case 1:
			R = qv;
			G = V;
			B = pv;
			break;
		case 2:
			R = pv;
			G = V;
			B = tv;
			break;
		case 3:
			R = pv;
			G = qv;
			B = V;
			break;
		case 4:
			R = tv;
			G = pv;
			B = V;
			break;
		case 5:
			R = V;
			G = pv;
			B = qv;
			break;
		case 6:
			R = V;
			G = tv;
			B = pv;
			break;
		case -1:
			R = V;
			G = pv;
			B = qv;
			break;
		default:
			R = G = B = V;
			break;
		}
	}
	rgb_color rgb;
	rgb.red=floor(R*255);
	rgb.green=floor(G*255);
	rgb.blue = floor(B*255);

	return rgb;
}

int rgb_color_compare(rgb_color a, rgb_color b){
  if(a.red!=b.red||a.green!=b.green||a.blue!=b.blue)return 0;
  return 1;
}