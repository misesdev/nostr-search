import { Suspense } from 'react';
import LoadingImage from './loading';
import ImageSearch from '@/components/search/ImageSearch';
import { SearchParams } from '@/types/types';

const ImageSearchPage = async ({ searchParams }: { searchParams: SearchParams }) => {

    const searchTerm = searchParams.searchTerm;

    return (
        <Suspense fallback={<LoadingImage />}>
            <ImageSearch searchTerm={searchTerm} />
        </Suspense>
    )    
}

export default ImageSearchPage
