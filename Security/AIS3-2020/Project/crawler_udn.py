from bs4 import BeautifulSoup
import requests
import json

file_pos = "temp.csv"
file_output = open(file_pos,"w+")

def get_index(key_word):
	for i in range(2, 3):
		url = "https://udn.com/api/more?page=" + str(i) + "&id=search:" + key_word + "&channelId=2&type=searchword&last_page=999"
		resp = requests.get(url)
		resp = resp.json()
		for item in resp["lists"]:
			try:
				print(item["titleLink"])
				title, content = get_content(item["titleLink"])
				if title is None or content is None:
					continue
				append_result(title, content, "Blue")
				print(title)
				print(content)
			except:
				print("ERR")
			print("--------------------------")

def get_content(link):
	resp = requests.get(link)
	soup = BeautifulSoup(resp.text, features="html.parser")
	title = soup.select_one(".article-content__title").string
	
	content_element = soup.select_one(".article-content__editor").find_all("p")
	content = ""
	for item in content_element:
		if item.text is not None:
			content += item.text
	return (title, content)

def append_result(title, content, ans):
	file_output.write(title.replace(',', ''))
	file_output.write(",")
	file_output.write(content.replace(',', ''))
	file_output.write(",")
	file_output.write(ans)
	file_output.write("\n")
	file_output.flush()

get_index("%E9%9F%93%E5%9C%8B%E7%91%9C")
keywords = ['韓國瑜', '中國', '疫情', '蔡英文', '陳菊', '監察院院長']
