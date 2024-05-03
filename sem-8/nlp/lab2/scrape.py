from bs4 import BeautifulSoup
import requests
import nltk
import os
from nltk import sent_tokenize, word_tokenize
import re
import urllib



nltk.download('stopwords')
nltk.download('punkt')

stop_words = set(nltk.corpus.stopwords.words('english'))





def fetch_html_page(url):
    # Fetch the page
    response = requests.get(url)
    return response.text



text_cleanup_regex = r'[^a-zA-Z0-9.\s]'

def extract_info(url, html_page):

    
    # Parse the page
    soup = BeautifulSoup(html_page, 'html.parser')
    title = soup.title.string.strip()
    # Extract the text
    text = soup.get_text()

    cleaned_text = re.sub(text_cleanup_regex,'', text)
    # remove \n characters
    cleaned_text = ' '.join(cleaned_text.split('\n'))
    # remove extra spaces
    cleaned_text = ' '.join(cleaned_text.split())
    # remove stop words
    cleaned_text = ' '.join([word for word in cleaned_text.split() if word not in stop_words])
  
    
    text = ' '.join(text.split())
    # write to file
    if not os.path.exists(title):
        os.mkdir(title)
    
    

    paras = soup.find_all('p')
    paras = [para.get_text() for para in paras if len(para.get_text().strip())>0]

    sentences = [sentence.strip() for sentence in sent_tokenize(cleaned_text) if len(sentence.strip())>0]
  

    words = word_tokenize(cleaned_text) 
    words = [word for word in words if re.match(r'[a-zA-Z]', word) is not None]


    links = soup.find_all('a')
    links = [str(link.get('href')) for link in links if link is not None]

    for i in range(len(links)):
        if links[i].startswith('/'):
            links[i] = urllib.parse.urljoin(url, links[i])
        elif links[i].startswith('#'):
            links[i] = url + links[i]
            
   


    with open(os.path.join(title, 'text.txt'), 'w') as f:
        f.write(text)
    with open(os.path.join(title, 'paras.txt'), 'w') as f:
        f.write('\n'.join(paras))

    with open(os.path.join(title, 'sentences.txt'), 'w') as f:
        f.write('\n'.join(sentences))
    with open(os.path.join(title, 'words.txt'), 'w') as f:
        f.write('\n'.join(words))
    with open(os.path.join(title, 'links.txt'), 'w') as f:
        f.write('\n'.join(links))


    return {
        'text': text, 
        'paragraphs':paras,
        'sentences': sentences,
        'words': words,
        'links': links
    }
    






test_url_1 = "https://www.bbc.co.uk/news"
test_url_2 = "https://en.wikipedia.org/wiki/2024_Chile_wildfires"

if __name__ == '__main__':
    url = test_url_2
    html = fetch_html_page(url)
 
    extracted_info = extract_info(url, html)
    print('Number of characters:', len(extracted_info['text']))
    print('Number of words:', len(extracted_info['words']))
    print('Number of sentences:', len(extracted_info['sentences']))
    print('Number of paragraphs:', len(extracted_info['paragraphs']))
    print('Number of links:', len(extracted_info['links']))


